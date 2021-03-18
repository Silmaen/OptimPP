#!/usr/bin/env python3
# - encoding: UTF-8 -
import os
from common import *


def main():
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
