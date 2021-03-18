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
    if runcommand("gcovr --version") == 0:
        return True
    return False


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


def get_gcov_program(build_dir: Path):
    fp = open(build_dir / "CMakeCache.txt", "r")
    lines = fp.readlines()
    fp.close()
    # Search for the used compiler
    compiler = ""
    for line in lines:
        if not line.startswith("CMAKE_CXX_COMPILER:STRING"):
            continue
        if "clang" in line:
            compiler = "clang"
            break
        if "g++" in line:
            compiler = "g++"
            break
    if compiler == "":
        print_log("Compiler not supported for coverage analysis", 3)
        return ""
    if compiler == "g++":
        if which("egcov"):
            return '"egcov"'
        else:
            return '"gcov"'
    if compiler == "clang":
        return '"llvm-cov gcov"'
    return ""


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
    gcov = get_gcov_program(build_dir)
    if have_gcovr() and have_coverage_infos(build_dir) and gcov not in ["", None]:
        # Directory change
        os.chdir(build_dir)
        cov_dir = build_dir / "Coverage"
        if cov_dir.exists():
            rmtree(cov_dir)
        cov_dir.mkdir(parents=True)
        os.chdir(cov_dir)

        # Run the coverage
        nbc = get_cpu_number()
        cmd = 'gcovr -v -r  ../../Source -o index.html --html-details -bup ' + ['--exclude-unreachable-branches', ""][
            "llvm" in gcov] + ' --exclude-throw-branches --gcov-executable=' + gcov
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
        with zipfile.ZipFile('coverage.zip', 'w') as my_zip:
            for file in os.listdir("."):
                if not file.endswith(".html"):
                    continue
                my_zip.write(file)
        move('coverage.zip', '../coverage.zip')

        # Directory restore
        os.chdir(src_root)

    print_log(" *** return code = " + str(ret), 4)
    exit(ret)


if __name__ == "__main__":
    main()
