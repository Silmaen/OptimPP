#!/usr/bin/env python3
# - encoding: UTF-8 -

from common import *


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
    parser.add_argument(
        "-s", "--staticAnalysis",
        action="store_true",
        help="If we should do the static analysis"
    )
    args = parser.parse_args()

    # Remove all previous build before create build directory
    build_dir = make_output_dir(args.compiler, args.debug)
    if build_dir.exists():
        from shutil import rmtree
        rmtree(build_dir, ignore_errors=True)
    build_dir.mkdir()

    # Construct the CMake command
    options = SupportedConfiguration[config_by_compiler(args.compiler)]
    cmd = find_program("cmake")
    cmd += " -S " + str(src_root) + " -B " + str(build_dir)
    cmd += " -DCMAKE_BUILD_TYPE=" + options["Build_Type"][args.debug]
    for key in options:
        if key in ["Minimum_version", "Build_Type"]:
            continue
        if key == "Toolchain":
            cmd += ' -G "' + options[key] + '"'
            continue
        cmd += " -DCMAKE_" + key.upper() + '="' + options[key] + '"'
    if args.staticAnalysis:
        scb = find_program("scan-build")
        scb += " " + make_scan_build_param(args.compiler, args.debug) + " " + cmd
    else:
        if "visual-studio" not in args.compiler:
            if args.compiler in ["gcc"]:
                cmd += " -DENABLE_CODE_COVERAGE=ON"

    # execute CMake command
    ret = runcommand(cmd)

    if args.staticAnalysis:
        ret = 0
    print_log(" *** return code = " + str(ret), 4)
    exit(ret)


if __name__ == "__main__":
    main()
