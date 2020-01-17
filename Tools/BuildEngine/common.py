# - encoding: UTF-8 -
import platform, sys, argparse, subprocess, os, shutil, time, zipfile, copy

SupportedCompiler = {"Windows":["MSVC","gcc/g++"],"OpenBSD":["egcc/eg++","clang/clang++"]}
SupportedCompilerShort = {"Windows":["MSVC","gcc"],"OpenBSD":["gcc","clang"]}
Corresponding = {"WindowsMSVC":"MSVC","Windowsgcc":"gcc/g++","OpenBSDgcc":"egcc/eg++","OpenBSDclang":"clang/clang++"}
OS = platform.system()
MAX_RM_TRY=50
if OS not in SupportedCompiler.keys():
    print("Unsupported OS: " + str(OS))
    sys.exit(1)
Compilers = SupportedCompiler[OS]
CompilersShort = SupportedCompilerShort[OS]
srcRoot= os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
BuildEnginePath = os.path.dirname(os.path.abspath(__file__))
buildDir=os.path.join(srcRoot,"Build")
ActionList = ["generate","build","test","doc","package"]
fullActionList = ["All"] + ActionList

PytonExe = "python"
if OS in ["OpenBSD"]:
    PytonExe+="3"

if os.getcwd() != srcRoot:
    #print("WARNING: not in the source's root directory",file=sys.stderr)
    os.chdir(srcRoot)

def safeRmTree(path,checkExistance:bool=True):
    '''
    function to safely delete folder with exception handling
    '''
    if not checkExistance and not os.path.exists(path):
        print("Warning: folder '"+path+"' does not exists for delete",file=sys.stderr)
    for i in range(MAX_RM_TRY):
        if os.path.exists(path):
            try:
                shutil.rmtree(path,ignore_errors=True)
            except Exception as e:
                time.sleep(0.05) #wait before retry
                continue
        else:
            break
    if os.path.exists(path):
        print("Warning: unable to delete folder "+path,file=sys.stderr)
    return

def runcommand(cmd:str):
    try:
        print(">>>"+cmd)
        ret = subprocess.run(cmd,shell=True,stdout=sys.stdout,stderr=sys.stderr).returncode
    except:
        print("errors!!")
        ret = -8
    return ret;

def runPython(pythonscript:str,params:list):
    try: 
        cmd = PytonExe+" "+pythonscript+" "+" ".join(params)
    except:
        print("bad Python command")
        return -87
    return runcommand(cmd)

def getCPUNumber():
    try:
        import multiprocessing
        return multiprocessing.cpu_count()
    except (ImportError, NotImplementedError):
        print("Error while finding number of processors")
        return 1