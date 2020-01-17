#!/usr/bin/env python3
# - encoding: UTF-8 -

import os,argparse,platform,sys,copy

srcRoot= os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
BuildEnginePath = os.path.join(os.path.dirname(os.path.abspath(__file__)),"BuildEngine")

SupportedCompiler = {"Windows":["MSVC","gcc"],"OpenBSD":["gcc","clang"]}
Corresponding = {"WindowsMSVC":"MSVC","Windowsgcc":"gcc/g++","OpenBSDgcc":"egcc/eg++","OpenBSDclang":"clang/clang++"}

ActionList = ["generate","build","test","doc","package"]

fullActionList = ["All"] + ActionList

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
    utestmake=os.path.join(srcRoot,"Build","Test","UnitTests","optimpp_unit_test")
    utestmsvc=os.path.join(srcRoot,"Build","Test","UnitTests","Debug","optimpp_unit_test.exe")
    if not (os.path.exists(utestmake) or os.path.exists(utestmake+".exe") or os.path.exists(utestmsvc)):
        print("ERROR: unable to test: please compile target 'optimpp_unit_test' first")
        sys.exit(3)
    coverinfo=os.path.join(srcRoot,"Build","test","UnitTests","CMakeFiles","optimpp_unit_test.dir","test.cpp.gcno")
    if os.path.exists(coverinfo):
        scr=os.path.join(BuildEnginePath,"runtestcoverage.py")
    else:
        scr=os.path.join(BuildEnginePath,"runtest.py")
    return os.system("python3 "+scr)

def documentation():
    scr=os.path.join(BuildEnginePath,"documentation.py")
    opt=""
    return os.system("python3 "+scr+opt)

def package():
    cmakelist=os.path.join(srcRoot,"Build","CMakeCache.txt")
    if not os.path.exists(cmakelist):
        print("ERROR: unable to package: pleease configure first")
        sys.exit(2);
    scr=os.path.join(BuildEnginePath,"package.py")
    return os.system("python3 "+scr)

def doAction(action,OSCompiler,Debug,Target):
    if action == "generate":
        generate(OSCompiler,Debug)
    elif action == "build":
        build(Target)
    elif action == "test":
        testncover()
    elif action == "doc":
        documentation()
    elif action == "package":
        package()
    else:
        print("ERROR: Unknown Action: '"+action+"'")

def main():
    Parser = argparse.ArgumentParser()
    Parser.add_argument("action",nargs='+',default=fullActionList[0],choices=fullActionList,help="what to do")
    Parser.add_argument("-c","--compiler",type=str,choices=Compilers,default=Compilers[0],help="The compiler to be used")
    Parser.add_argument("-g","--debug",action="store_true",help="If we should compile in Debug mode")
    Parser.add_argument("-t","--target",type=str,help="The compiler target")
    args = Parser.parse_args()
    # filling up the todo list
    todo = []
    if "all" in args.action:
        todo = copy.deepcopy(ActionList)
    else:
        for a in ActionList:
            if a in args.action:
                todo.append(a)
    # execute the todo list
    for action in todo:
        doAction(action,OS+args.compiler,args.debug,args.target)

if __name__ == "__main__":
    main()
