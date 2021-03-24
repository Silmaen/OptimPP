#!/usr/bin/env python3
# - encoding: UTF-8 -
import shutil
from argparse import ArgumentParser
from copy import deepcopy

from BuildEngine.common import *


def gogo(cmake_path, build_dir, compiler, debug, options):
    cmd = [cmake_path]
    cmd += [' -S "' + str(src_root) + '"', ' -B "' + str(build_dir) + '"']
    cmd += [" -DCMAKE_BUILD_TYPE=" + ["Release", "Debug"][debug]]
    for key in options:
        if key in ["Minimum_version", "Build_Type"]:
            continue
        if key == "Toolchain":
            cmd += [' -G "' + options[key] + '"']
            continue
        cmd += [" -DCMAKE_" + key.upper() + '="' + options[key] + '"']
    if debug and compiler in ["gcc", "clang"]:
        cmd += [" -DENABLE_CODE_COVERAGE=ON"]
    return cmd


def do_action(action, compiler, debug):
    build_dir = make_output_dir(compiler, debug)
    cmake_path = find_program("cmake")
    options = SupportedConfiguration[config_by_compiler(compiler)]
    nbc = get_cpu_number()
    if action == "clear":
        shutil.rmtree(build_dir, ignore_errors=True)
        build_dir.mkdir(parents=True, exist_ok=True)
    elif action == "generate":
        cmd = gogo(cmake_path, build_dir, compiler, debug, options)
        return runcommand(" ".join(cmd))
    elif action == "build":
        cmd = [cmake_path, "--build " + str(build_dir)]
        nbc = get_cpu_number()
        if nbc > 1:
            cmd += [" -j "+str(nbc)]
        return runcommand(" ".join(cmd))
    elif action == "test":
        cmd = [cmake_path, "--build " + str(build_dir), "-t test-and-coverage"]
        nbc = get_cpu_number()
        if nbc > 1:
            cmd += [" -j "+str(nbc)]
        return runcommand(cmd)
    elif action == "doc":
        cmd = [cmake_path, "--build " + str(build_dir), "-t Documentation"]
        if nbc > 1:
            cmd += [" -j "+str(nbc)]
        return runcommand(cmd)
    elif action == "StaticAnalysis":
        scb = find_program("scan-build")
        cmd = scb + " " + str(build_dir) + " " + " ".join(gogo(cmake_path, build_dir, "clang", True, options))
        ret = runcommand(cmd)
        if ret != 0:
            return ret
        cmd = find_program("scan-build")
        cmd += " " + make_scan_build_param("clang", True) + " make -j" + str(nbc)
        return runcommand(cmd)
    elif action == "package":
        cmd = [cmake_path, "--build " + str(build_dir), "-t Packaging"]
        if nbc > 1:
            cmd += [" -j "+str(nbc)]
        return runcommand(cmd)
    else:
        return 1
    return 0


def main():
    parser = ArgumentParser()
    parser.add_argument(
        "action",
        nargs='+',
        choices=ActionList2,
        help="what to do"
    )
    compilers = get_compiler_for_os()
    parser.add_argument(
        "-c", "--compiler",
        type=str,
        choices=compilers,
        default=compilers[0],
        help="The compiler to be used")
    parser.add_argument(
        "-g", "--debug",
        action="store_true",
        help="If we should compile in Debug mode"
    )
    parser.add_argument(
        "-s", "--staticAnalysis",
        action="store_true",
        help="If we should do the static analysis"
    )
    args = parser.parse_args()
    # Filling up the action list
    todo = []
    if "All" in args.action:
        todo = deepcopy(ActionList2)
    else:
        for a in ActionList:
            if a in args.action:
                todo.append(a)
        # Execute the list of action
    for action in todo:
        ret = do_action(action, args.compiler, args.debug)
        if ret != 0:
            exit(ret)

    # Final message
    print_log("Everything ends up quite well!", 4)

if __name__ == "__main__":
    main()
