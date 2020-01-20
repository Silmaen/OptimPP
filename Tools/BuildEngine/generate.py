#!/usr/bin/env python3
# - encoding: UTF-8 -
from common import *

Parser = argparse.ArgumentParser()
Parser.add_argument("-c","--compiler",type=str,choices=Compilers,default=Compilers[0],help="The compiler to be used")
Parser.add_argument("-g","--debug",action="store_true",help="If we should compile in Debug mode")
Parser.add_argument("-s","--staticAnalysis",action="store_true",help="If we should do the static analysis")
Parser.add_argument("--undefinedBehavior","-u",action="store_true",help="")
args = Parser.parse_args()

# remove all previous build before create build directory
safeRmTree(buildDir)
os.mkdir(buildDir)

# build type
btype=" -DCMAKE_BUILD_TYPE=Release"
if args.debug:
    btype=" -DCMAKE_BUILD_TYPE=Debug"

# definition of the CMake command
if OS == "Windows":
    cmd='"C:\\Program Files\\CMake\\bin\\cmake.exe"'
else:
    cmd="cmake"
cmd+=" -S "+srcRoot+" -B "+buildDir
if args.staticAnalysis and OS == "OpenBSD":
    cmd = "scan-build " +ScanbuildParam + " " + cmd
else:
    if args.compiler != "MSVC":
        c,cxx= args.compiler.split("/")
        if OS == "Windows":
            if shutil.which("sh") is not None:
                cmd+=' -G "MSYS Makefiles"'
            else:
                cmd+=' -G "MinGW Makefiles"'
        cmd+=" -DCMAKE_C_COMPILER="+c+" -DCMAKE_CXX_COMPILER="+cxx
        cmd+=" -DENABLE_CODE_COVERAGE=ON"
        if "clang" in c:
            if args.undefinedBehavior:
                cmd=cmd+" -DENABLE_UNDEFINED_BEHAVIOR_SANITIZER=ON"
    else:
        cmd+=" -DCMAKE_GENERATOR_PLATFORM=x64"
    cmd+=btype

# execute CMake command
ret = runcommand(cmd)

if args.staticAnalysis:
    ret = 0
print(" *** return code = "+str(ret) )
sys.exit(ret)
