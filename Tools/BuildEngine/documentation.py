#!/usr/bin/env python3
# - encoding: UTF-8 -
import os
from argparse import ArgumentParser

from common import *


def main():

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
    doxygen_file = src_root / "doc" / "Doxyfile"

    cc = os.getcwd()
    os.chdir(src_root)

    cmd = find_program("doxygen")
    ret = runcommand(str(cmd) + " " + str(doxygen_file))

    os.chdir(cc)

    print_log(" *** return code = " + str(ret), 4)
    exit(ret)


if __name__ == "__main__":
    main()
