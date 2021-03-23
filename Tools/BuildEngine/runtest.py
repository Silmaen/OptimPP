#!/usr/bin/env python3
# - encoding: UTF-8 -
import os
import zipfile
from shutil import rmtree, which, move

from common import *

# ==================================================
# Construction of the CMake command
cmdT = find_program("ctest")
testcmd = cmdT + " -V -D Experimental"
# adding parameters
sub_cmd = ["Start", "Test"]
# gcovr options
gcovrExclusions = ['"(.+/)?Test(.+/)?"', '"(.+/)?main.cpp(.+/)?"']
gcovrSources = ['../Test/UnitTests', '../Source']


# ==================================================
def have_gcovr():
    if not which("gcovr"):
        print_log("No Gcovr found for generating coverage report", 1)
        exit(1)


def have_coverage_infos(build_dir: Path):
    gcno = False
    for root, dirs, files in os.walk(build_dir):
        for file in files:
            if file.endswith(".gcno"):
                gcno = True
                break
        if gcno:
            break
    return gcno


# run
def main():
    from argparse import ArgumentParser
    parser = ArgumentParser()
    compilers = get_compiler_for_os()
    parser.add_argument(
        "-c", "--compiler",
        type=str,
        choices=compilers,
        default=compilers[0],
        help="The compiler to be used"
    )
    parser.add_argument(
        "-g", "--debug",
        action="store_true",
        help="If we should compile in Debug mode"
    )
    args = parser.parse_args()
    build_dir = make_output_dir(args.compiler, args.debug)
    cmake_cache = get_cmake_vars(args.compiler, args.debug)

    # ---------------------
    # Run the test
    # ---------------------
    os.chdir(build_dir)
    ret = 0
    for s in sub_cmd:
        ret = runcommand(testcmd + s)
        if ret != 0:
            print_log(" *** /!\\ Error during test run, return code = " + str(ret))
            exit(ret)

    # ---------------------
    # Analyse the coverage
    # ---------------------
    if cmake_cache.get("ENABLE_CODE_COVERAGE"):
        print_log("Coverage enabled", 4)
        have_gcovr()
        gcov = cmake_cache.get("OPP_COVERAGE_COMMAND")
        if have_coverage_infos(build_dir):

            # Directory change
            os.chdir(build_dir)
            print_log("**** Generate coverage report ", 4)
            cov_dir = cmake_cache.get("CMAKE_COVERAGE_OUTPUT_DIRECTORY")
            if cov_dir.exists():
                rmtree(cov_dir)
            cov_dir.mkdir(parents=True)
            os.chdir(cov_dir)

            # Run the coverage
            nbc = get_cpu_number()
            cmd = 'gcovr -v -r  ../../Source -o index.html --html-details -bup ' + ['--exclude-unreachable-branches', ""][
                "llvm" in str(gcov)] + ' --exclude-throw-branches --gcov-executable=' + str(gcov)
            for ex in gcovrExclusions:
                cmd += ' -e ' + ex
            for sr in gcovrSources:
                cmd += ' ' + sr
            if nbc > 1:
                cmd += " -j " + str(nbc)
            ret = runcommand(cmd)
            if ret != 0:
                print_log(" *** /!\\ Error during Coverage analysis, return code = " + str(ret))
                exit(ret)

            # Artifact creation
            print_log("**** Archive coverage report ", 4)
            with zipfile.ZipFile('coverage.zip', 'w') as my_zip:
                for file in os.listdir("."):
                    if not file.endswith(".html"):
                        continue
                    my_zip.write(file)
            move('coverage.zip', build_dir / 'coverage.zip')
            print_log("**** Archive coverage generated: '" + str(build_dir / 'coverage.zip') + "'", 4)

            # Directory restore
            os.chdir(src_root)

    print_log(" *** return code = " + str(ret), 4)
    exit(ret)


if __name__ == "__main__":
    main()
