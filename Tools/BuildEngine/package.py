#!/usr/bin/env python3
# - encoding: UTF-8 -
from common import *

zipname="optimpp.zip"
foldertozip=["bin","doc"]

def main():
    os.chdir(buildDir)
    zipf = zipfile.ZipFile(zipname, 'w')
    for f in foldertozip:
        if not os.path.exists(f):
            continue
        for root, dirs, files in os.walk(f):
            for file in files:
                zipf.write(os.path.join(root, file))
    zipf.close()
    endCommand(0)

if __name__ == "__main__":
    main()
