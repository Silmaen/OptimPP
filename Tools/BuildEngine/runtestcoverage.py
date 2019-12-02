#!/usr/bin/env python3
# - encoding: UTF-8 -
from common import *

# definition of the CMake command
if OS == "Windows":
    cmdT='"C:\\Program Files\\CMake\\bin\\ctest.exe"'
    cmd='"C:\\Program Files\\CMake\\bin\\cmake.exe"'
else:
    cmdT="ctest"
    cmd="cmake"

nbc= getCPUNumber()
jobs=""
if nbc>1:
    jobs+=" -j"+str(nbc)

# adding parameters
subcmd=[cmdT+" -V -D ExperimentalStart",
        #cmd+" --build . --target cg_unit_test"+jobs,
        cmdT+" -V -D ExperimentalTest"]

#run
os.chdir(buildDir)
for s in subcmd:
    runcommand(s)

os.chdir(buildDir)
safeRmTree("Coverage")
os.mkdir("Coverage")
os.chdir("Coverage")

if shutil.which("egcov"):
    cmdGcov="egcov"
else:
    cmdGcov="gcov"

runcommand('gcovr -r  ../.. -o index.html --html-details -bup -e "(.+/)?test(.+/)?" --gcov-executable '+cmdGcov+' --exclude-unreachable-branches ../test/UnitTests/CMakeFiles/cg_unit_test.dir')
with zipfile.ZipFile('coverage.zip', 'w') as myzip:
    for file in os.listdir("."):
        if not file.endswith(".html"):
            continue
        myzip.write(file)
shutil.move('coverage.zip','../coverage.zip')

os.chdir(srcRoot)