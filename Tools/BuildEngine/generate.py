#!/usr/bin/env python3
# - encoding: UTF-8 -
from common import *

def generStaticAnalysis():
    cmd = getCMakeProgram() + " -DCMAKE_BUILD_TYPE=Debug -S "+srcRoot+" -B "+buildDir
    cmd = "scan-build " +ScanbuildParam + " " + cmd
    ret = runcommand(cmd)
    return 0

def generBuildConfig(dbg:bool, compiler:str):
    # build type
    btype=" -DCMAKE_BUILD_TYPE=Release"
    if dbg:
        btype=" -DCMAKE_BUILD_TYPE=Debug"
    cmd = getCMakeProgram() + " -S " + srcRoot+" -B " + buildDir
    if "MSVC" not in compiler and "visual-studio" not in compiler:
        c,cxx= compiler.split("/")
        if "clang" in c:
        #    c,cxx = getClangCompilers()
            pass
        else:
            if OS == "Windows":
                if shutil.which("sh") is not None:
                    cmd+='-G "CodeBlocks - MinGW Makefiles"'
                else:
                    cmd+=' -G "CodeBlocks - MinGW Makefiles"'
        cmd+=" -DCMAKE_C_COMPILER="+c+" -DCMAKE_CXX_COMPILER="+cxx
        if "clang" not in compiler or OS != "OpenBSD":
            cmd+=" -DENABLE_CODE_COVERAGE=ON"
    else:
        cmd+=" -DCMAKE_GENERATOR_PLATFORM=x64"
    cmd+=btype
    # execute CMake command
    ret = runcommand(cmd)
    return ret

def main():
    Parser = argparse.ArgumentParser()
    Parser.add_argument("-c","--compiler",type=str,choices=Compilers,default=Compilers[0],help="The compiler to be used")
    Parser.add_argument("-g","--debug",action="store_true",help="If we should compile in Debug mode")
    Parser.add_argument("-s","--staticAnalysis",action="store_true",help="If we should do the static analysis")
    args = Parser.parse_args()
    # remove all previous build before create build directory
    safeRmTree(buildDir)
    os.mkdir(buildDir)
    if args.staticAnalysis:
        ret = generStaticAnalysis()
    else:
        ret = generBuildConfig(args.debug, args.compiler)
    endCommand(ret)

if __name__ == "__main__":
    main()
