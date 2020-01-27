#!/usr/bin/env python3
# - encoding: UTF-8 -
from common import *

def main():
    doxyfile=os.path.join(srcRoot,"doc","Doxyfile")
    ret = runcommand("doxygen " + doxyfile)
    endCommand(ret)

if __name__ == "__main__":
    main()
