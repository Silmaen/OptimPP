#!/usr/bin/env python3
# - encoding: UTF-8 -
import os
import zipfile

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
        "-t", "--target",
        type=str,
        help="The compiler target"
    )
    parser.add_argument(
        "-s", "--staticAnalysis",
        action="store_true",
        help="If we should do the static analysis"
    )
    args = parser.parse_args()

    build_dir = make_output_dir(args.compiler, args.debug)
    if not build_dir.exists():
        print_log("trying to compile a non configured options")
        exit(4)
    os.chdir(build_dir)
    cmd = find_program("cmake")
    cmd += " --build ."
    if args.target not in [None, ""]:
        cmd += " --target " + args.target
    nbc = get_cpu_number()
    # if nbc>1:
    #    cmd+=" -j"+str(nbc)

    if args.staticAnalysis:
        cmd = find_program("scan-build")
        cmd += " " + make_scan_build_param(args.compiler, args.debug) + " make -j" + str(nbc)

    ret = runcommand(cmd)

    if args.staticAnalysis:
        if ret == 0:
            os.makedirs(os.path.join("static-analysis", "noerror"))
            fp = open(os.path.join("static-analysis", "noerror", "index.html"), "w")
            fp.write("No bug found!! yes!")
            fp.close()
        zipf = zipfile.ZipFile("StaticAnalysis.zip", 'w')
        os.chdir("static-analysis")
        os.chdir(os.listdir(".")[-1])
        for f in os.listdir("."):
            zipf.write(f)
        zipf.close()
        ret = 0

    os.chdir(src_root)
    print_log(" *** return code = " + str(ret), 4)
    exit(ret)


if __name__ == "__main__":
    main()
