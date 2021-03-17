#!/usr/bin/env python3
# - encoding: UTF-8 -
from BuildEngine.common import *


def generate(cc: str, debug: bool, static_analysis: bool):
    if cc not in get_compiler_for_os():
        print("ERROR: unknown config compiler:" + cc)
        exit(1)
    config = config_by_compiler(cc)
    scr = build_engine / "generate.py"
    opt = []
    if debug:
        opt += ["-g"]
    if static_analysis:
        opt += ['-s']
    else:
        opt += ["-c " + cc]
    return run_python(scr, opt)


def build(cc: str, debug: bool, target: str, static_analysis: bool):
    cmake_cache = make_output_dir(cc, debug) / "CMakeCache.txt"
    if not cmake_cache.exists():
        print("ERROR: unable to compile: please configure first")
        exit(2)
    scr = build_engine / "compile.py"
    opt = ['-c ' + cc]
    if debug:
        opt += ['-g']
    if static_analysis:
        opt += ['-s']
    else:
        if target not in [None, ""]:
            opt += ["-t " + target]
    return run_python(scr, opt)


def testncover(cc: str, debug: bool):
    cmake_cache = make_output_dir(cc, debug) / "CMakeCache.txt"
    if not cmake_cache.exists():
        print("ERROR: unable to test: please configure first")
        exit(2)
    unit_test_dir = make_output_dir(cc, debug) / "Test" / "UnitTests"
    unit_test_make = unit_test_dir / "optimpp_unit_test"
    unit_test_make_w = unit_test_dir / "optimpp_unit_test.exe"
    unit_test_msvc = unit_test_dir / "Debug" / "optimpp_unit_test.exe"
    if not (unit_test_make.exists() or unit_test_make_w.exists() or unit_test_msvc.exists()):
        print("ERROR: unable to test: please compile target 'optimpp_unit_test' first")
        exit(3)
    coverinfo = unit_test_dir / "CMakeFiles" / "optimpp_unit_test.dir" / "test.cpp.gcno"
    if coverinfo.exists():
        scr = build_engine / "runtestcoverage.py"
    else:
        scr = build_engine / "runtest.py"
    opt = ['-c ' + cc]
    if debug:
        opt += ['-g']
    return run_python(scr, opt)


def documentation(cc: str, debug: bool):
    scr = build_engine / "documentation.py"
    return run_python(scr, [])


def do_action(action, compiler, debug, target, static_analysis):
    """
    Do the action
    :param action:
    :param compiler:
    :param debug:
    :param target:
    :param static_analysis:
    :return:
    """
    if action == "generate":
        return generate(compiler, debug, static_analysis)
    elif action == "build":
        return build(compiler, debug, target, static_analysis)
    elif action == "test":
        return testncover(compiler, debug)
    elif action == "doc":
        return documentation(compiler, debug)
    else:
        print("ERROR: Unknown Action: '" + action + "'")
        return -98


def main():
    from argparse import ArgumentParser
    from copy import deepcopy
    if not check_os():
        print("ERROR: unsupported OS")
        exit(1)

    parser = ArgumentParser()
    parser.add_argument(
        "action",
        nargs='+',
        default=fullActionList[0],
        choices=fullActionList,
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
    parser.add_argument(
        "-t", "--target",
        type=str,
        help="The compiler target"
    )
    args = parser.parse_args()

    # Filling up the action list
    todo = []
    if args.staticAnalysis:
        todo.append("generate")
        todo.append("build")
    elif "All" in args.action:
        todo = deepcopy(ActionList)
    else:
        for a in ActionList:
            if a in args.action:
                todo.append(a)

    # Execute the list of action
    for action in todo:
        ret = do_action(action, args.compiler, args.debug, args.target, args.staticAnalysis)
        if ret != 0:
            exit(ret)

    # Final message
    print("Everything ends up quite well!")


if __name__ == "__main__":
    main()
