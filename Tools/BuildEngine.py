#!/usr/bin/env python3
# - encoding: UTF-8 -
from BuildEngine.common import *

def generate(cc:str,debug:bool,undefinedBehavior:bool, addressSanitizer:bool, staticAnalysis:bool):
    if cc not in Corresponding:
        print("ERROR: unknown config compiler:"+cc)
        sys.exit(1)
    scr=os.path.join(BuildEnginePath,"generate.py")
    opt = ["-c "+Corresponding[cc]]
    if debug:
        opt += ["-g"]
    if undefinedBehavior:
        opt += ['-u']
    if addressSanitizer:
        opt += ['-a']
    if staticAnalysis:
        opt += ['-s']
    return runPython(scr,opt)

def build(target:str, staticAnalysis:bool):
    cmakelist=os.path.join(srcRoot,"Build","CMakeCache.txt")
    if not os.path.exists(cmakelist):
        print("ERROR: unable to compile: please configure first")
        sys.exit(2);
    scr=os.path.join(BuildEnginePath,"compile.py")
    opt=[]
    if target not in [None,""]:
        opt+=["-t "+target]
    if staticAnalysis:
        opt += ['-s']
    return runPython(scr,opt)

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
    return runPython(scr,[])

def documentation():
    scr=os.path.join(BuildEnginePath,"documentation.py")
    return runPython(scr,[])

def package():
    cmakelist=os.path.join(srcRoot,"Build","CMakeCache.txt")
    if not os.path.exists(cmakelist):
        print("ERROR: unable to package: pleease configure first")
        sys.exit(2);
    scr=os.path.join(BuildEnginePath,"package.py")
    return runPython(scr,[])

def doAction(action,OSCompiler,Debug,Target,undefinedBehavior, addressSanitizer, staticAnalysis):
    if action == "generate":
        return generate(OSCompiler,Debug,undefinedBehavior, addressSanitizer, staticAnalysis)
    elif action == "build":
        return build(Target, staticAnalysis)
    elif action == "test":
        return testncover()
    elif action == "doc":
        return documentation()
    elif action == "package":
        return package()
    else:
        print("ERROR: Unknown Action: '"+action+"'")
        return -98

def main():
    Parser = argparse.ArgumentParser()
    Parser.add_argument("action",nargs='+',default=fullActionList[0],choices=fullActionList,help="what to do")
    Parser.add_argument("-c","--compiler",type=str,choices=CompilersShort,default=CompilersShort[0],help="The compiler to be used")
    Parser.add_argument("-g","--debug",action="store_true",help="If we should compile in Debug mode")
    Parser.add_argument("-s","--staticAnalysis",action="store_true",help="If we should do the static analysis")
    Parser.add_argument("--undefinedBehavior","-u",action="store_true",help="")
    Parser.add_argument("--addressSanitizer","-a",action="store_true",help="")
    Parser.add_argument("-t","--target",type=str,help="The compiler target")
    args = Parser.parse_args()
    # filling up the todo list
    todo = []
    if "All" in args.action:
        todo = copy.deepcopy(ActionList)
    else:
        for a in ActionList:
            if a in args.action:
                todo.append(a)
    # execute the todo list
    for action in todo:
        ret = doAction(action, OS+args.compiler, args.debug, args.target, args.undefinedBehavior, args.addressSanitizer, args.staticAnalysis)
        if ret != 0:
            sys.exit(ret)

if __name__ == "__main__":
    main()
