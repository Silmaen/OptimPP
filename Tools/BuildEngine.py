#!/usr/bin/env python3
# - encoding: UTF-8 -

import os,argparse,platform,sys

srcRoot= os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
BuildEnginePath = os.path.join(os.path.dirname(os.path.abspath(__file__)),"BuildEngine")

SupportedCompiler = {"Windows":["MSVC","gcc"],"OpenBSD":["gcc","clang"]}
Corresponding = {"WindowsMSVC":"MSVC","Windowsgcc":"gcc/g++","OpenBSDgcc":"egcc/eg++","OpenBSDclang":"clang/clang++"}

OS = platform.system()
if OS not in SupportedCompiler.keys():
    print("Unsupported OS: " + str(OS))
    sys.exit(1)
Compilers = SupportedCompiler[OS]

def generate(cc:str,debug:bool):
    if cc not in Corresponding:
        print("ERROR: unknown config compiler:"+cc)
        sys.exit(1)
    scr=os.path.join(BuildEnginePath,"generate.py")
    return os.system("python3 "+scr+" -c "+Corresponding[cc]+[""," -g"][debug])

def build(target:str):
    cmakelist=os.path.join(srcRoot,"Build","CMakeCache.txt")
    if not os.path.exists(cmakelist):
        print("ERROR: unable to compile: please configure first")
        sys.exit(2);
    scr=os.path.join(BuildEnginePath,"compile.py")
    opt=""
    if target not in [None,""]:
        opt=" -t "+target
    return os.system("python3 "+scr+opt)

def testncover():
    cmakelist=os.path.join(srcRoot,"Build","CMakeCache.txt")
    if not os.path.exists(cmakelist):
        print("ERROR: unable to test: please configure first")
        sys.exit(2);
    utestmake=os.path.join(srcRoot,"Build","test","UnitTests","optimpp_unit_test")
    utestmsvc=os.path.join(srcRoot,"Build","test","UnitTests","Debug","optimpp_unit_test.exe")
    if not (os.path.exists(utestmake) or os.path.exists(utestmake+".exe") or os.path.exists(utestmsvc)):
        print("ERROR: unable to test: please compile target 'optimpp_unit_test' first")
        sys.exit(3)
    coverinfo=os.path.join(srcRoot,"Build","test","UnitTests","CMakeFiles","optimpp_unit_test.dir","test.cpp.gcno")
    if os.path.exists(coverinfo):
        scr=os.path.join(BuildEnginePath,"runtestcoverage.py")
    else:
        scr=os.path.join(BuildEnginePath,"runtest.py")
    return os.system("python3 "+scr)

def package():
    cmakelist=os.path.join(srcRoot,"Build","CMakeCache.txt")
    if not os.path.exists(cmakelist):
        print("ERROR: unable to package: pleease configure first")
        sys.exit(2);
    scr=os.path.join(BuildEnginePath,"package.py")
    return os.system("python3 "+scr)

Parser = argparse.ArgumentParser()
Parser.add_argument("action",type=str,choices=["all","generate","build","test","coverage","package"],help="what to do")
Parser.add_argument("-c","--compiler",type=str,choices=Compilers,default=Compilers[0],help="The compiler to be used")
Parser.add_argument("-g","--debug",action="store_true",help="If we should compile in Debug mode")
Parser.add_argument("-t","--target",type=str,help="The compiler target")
args = Parser.parse_args()


print("this file = " + __file__)
print("source root = " + srcRoot)


if args.action =="coverage":
    gen=False
    ccache=os.path.join(srcRoot,"Build","CMakeCache.txt")
    if not os.path.exists(ccache):
        gen=True
    else:
        f=open(ccache,"r")
        lines=f.readlines()
        f.close()
        for line in lines:
            if not  line.startswith("CMAKE_CXX_COMPILER"):
                continue
            if "g++" not in line:
                gen=False
            break
    if gen:
        generate(OS+"gcc")
    build("cg_unit_test")==0
    testncover()

if args.action in ["generate","all"]:
    generate(OS+args.compiler,args.debug)
if args.action in ["build","all"]:
    build(args.target)
if args.action in ["test","all"]:
    testncover()
if args.action in ["package","all"]:
    package()
