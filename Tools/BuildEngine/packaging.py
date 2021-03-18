#!/usr/bin/env python3
# - encoding: UTF-8 -
import os
import sys
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
    args = parser.parse_args()

    print("compiler: " + str(args.compiler))
    print("debug?: " + str(args.debug))
    # Remove all previous build before create build directory
    build_dir = make_output_dir(args.compiler, args.debug)
    if not build_dir.exists():
        print("ERROR: build directory does not exists", file=sys.stderr)
        exit(1)

    if (doc_build_dir / 'documentation.zip').exists():
        print("Extracting doc")
        zipfile.ZipFile(doc_build_dir / 'documentation.zip').extractall(build_dir / 'documentation')

    os.chdir(build_dir)
    print("creating: " + str((build_dir / 'optimpp.zip').absolute()))
    with zipfile.ZipFile(build_dir / 'optimpp.zip', 'w') as my_zip:
        zip_folder(my_zip, 'bin')
        zip_folder(my_zip, 'lib', ["gtest"])
        if (build_dir / 'documentation').exists():
            zip_folder(my_zip, 'documentation')
    print("done ")


if __name__ == "__main__":
    main()
