# - encoding: UTF-8 -
import platform
import sys
import argparse
import subprocess
import os
import shutil
import time
import zipfile

SupportedCompiler = {"Windows":["MSVC","gcc/g++"],"OpenBSD":["egcc/eg++","clang/clang++"]}
CompileModes = ["LOCAL","SERVER","BUILDER","COVERAGE","PROFILING"]

OS = platform.system()
MAX_RM_TRY=50

if OS not in SupportedCompiler.keys():
    print("Unsupported OS: " + str(OS))
    sys.exit(1)

Compilers = SupportedCompiler[OS]

srcRoot= os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
buildDir=os.path.join(srcRoot,"Build")

if os.getcwd() != srcRoot:
    #print("WARNING: not in the source's root directory",file=sys.stderr)
    os.chdir(srcRoot)

from pathlib import Path
def findMSBuild():
    if platform.system()!="Windows":
        return []
    fileList=[]
    # search in Program Files
    for filename in Path(os.environ["ProgramFiles"]).rglob('MSBuild.exe'):
        if "64" in str(filename):fileList.append(filename)
    # search in Program Files x86
    for filename in Path(os.environ["ProgramFiles(x86)"]).rglob('MSBuild.exe'):
        if "64" in str(filename):fileList.append(filename)
    return fileList

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
        ret = subprocess.call(cmd,shell=True,stdout=sys.stdout,stderr=sys.stderr)
        print("<<< "+str(ret))
    except:
        print("errors!!")
        sys.exit(1)
    if ret !=0:
        sys.exit(ret)

def getCPUNumber():
    try:
        import multiprocessing
        return multiprocessing.cpu_count()
    except (ImportError, NotImplementedError):
        print("Error while finding number of processors")
        return 1