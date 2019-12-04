#!/usr/bin/env python3
# - encoding: UTF-8 -
from common import *

# definition of the CMake command
if OS == "Windows":
    cmdT='"C:\\Program Files\\CMake\\bin\\ctest.exe"'
else:
    cmdT="ctest"
    
# adding parameters
subcmd=["Start","Test"]
cmd=cmdT+" -V -D Experimental"
#run
os.chdir(buildDir)
for s in subcmd:
    runcommand(cmd+s)

gcnodir = os.path.join(buildDir,"Test","UnitTests","CMakeFiles","optimpp_unit_test.dir")
doCoverage=False
if os.path.exists(gcnodir):
    list = os.listdir(gcnodir)
    for f in list:
        if f.endswith(".gcno"):
            doCoverage=True
            break

if (doCoverage):
    os.chdir(buildDir)
    safeRmTree("Coverage")
    os.mkdir("Coverage")
    os.chdir("Coverage")

    if shutil.which("egcov"):
        cmdGcov="egcov"
    else:
        cmdGcov="gcov"

    runcommand('gcovr -r  ../.. -o index.html --html-details -bup -e "(.+/)?Test(.+/)?" --gcov-executable '+cmdGcov+' --exclude-unreachable-branches ../Test/UnitTests/CMakeFiles/optimpp_unit_test.dir ../Source/CMakeFiles/optimpplib.dir')
    with zipfile.ZipFile('coverage.zip', 'w') as myzip:
        for file in os.listdir("."):
            if not file.endswith(".html"):
                continue
            myzip.write(file)
    shutil.move('coverage.zip','../coverage.zip')

    os.chdir(srcRoot)