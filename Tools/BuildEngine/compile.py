#!/usr/bin/env python3
# - encoding: UTF-8 -
from common import *
os.chdir(buildDir)

Parser = argparse.ArgumentParser()
Parser.add_argument("-t","--target",type=str,help="The compiler target")
args = Parser.parse_args()

if OS == "Windows":
    cmd='"C:\\Program Files\\CMake\\bin\\cmake.exe"'
else:
    cmd="cmake"
cmd+=" --build ."
if args.target not in [None,""]:
    cmd+=" --target "+args.target
nbc= getCPUNumber()
nbc=1
if nbc>1:
    cmd+=" -j"+str(nbc)

runcommand(cmd)

os.chdir(srcRoot)

