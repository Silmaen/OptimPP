#!/usr/bin/env python3
# - encoding: UTF-8 -
from common import *
os.chdir(buildDir)

Parser = argparse.ArgumentParser()
args = Parser.parse_args()

zipname="optimpp.zip"

zipf = zipfile.ZipFile(zipname, 'w')
foldertozip=["bin","doc"]

for f in foldertozip:
    if not os.path.exists(f):
        continue
    for root, dirs, files in os.walk(f):
        for file in files:
            zipf.write(os.path.join(root, file))
zipf.close()

os.chdir(srcRoot)

