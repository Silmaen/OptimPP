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