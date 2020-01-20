#!/usr/bin/env python3
# - encoding: UTF-8 -
from common import *
os.chdir(buildDir)

Parser = argparse.ArgumentParser()
Parser.add_argument("-t","--target",type=str,help="The compiler target")
Parser.add_argument("-s","--staticAnalysis",action="store_true",help="If we should do the static analysis")
args = Parser.parse_args()

if OS == "Windows":
    cmd='"C:\\Program Files\\CMake\\bin\\cmake.exe"'
else:
    cmd="cmake"
cmd+=" --build ."
if args.target not in [None,""]:
    cmd+=" --target "+args.target
nbc= getCPUNumber()
if nbc>1:
    cmd+=" -j"+str(nbc)

if args.staticAnalysis:
    cmd = "scan-build " + ScanbuildParam + " make -j" + str(nbc)

ret = runcommand(cmd)

os.chdir(srcRoot)

if args.staticAnalysis:
#    if ret == 0:
#        os.makedirs(os.path.join(staticanalysisdir,"noerror"))
#        fp = open(os.path.join(staticanalysisdir,"noerror","index.html"),"w")
#        fp.write("No bug found!! yes!")
#        fp.close()
    ret = 0
print(" *** return code = "+str(ret) )
sys.exit(ret)
