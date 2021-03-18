#!/usr/bin/env python3
# - encoding: UTF-8 -
import os
import zipfile

from common import *


def main():
    doxygen_file = src_root / "doc" / "Doxyfile"
    cc = os.getcwd()
    os.chdir(src_root)
    cmd = find_program("doxygen")
    ret = runcommand(str(cmd) + " " + str(doxygen_file))

    # Package the doc
    if ret == 0:
        os.chdir(doc_build_dir / "html")
        with zipfile.ZipFile(doc_build_dir / 'documentation.zip', 'w') as my_zip:
            zip_folder(my_zip, ".")

    os.chdir(cc)
    print_log(" *** return code = " + str(ret), 4)
    exit(ret)


if __name__ == "__main__":
    main()
