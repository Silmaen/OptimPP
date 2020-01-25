#!/usr/bin/env python3
# - encoding: UTF-8 -
from common import *

#==================================================
# definition of the CMake command
if OS == "Windows":
    cmdT = '"C:\\Program Files\\CMake\\bin\\ctest.exe"'
else:
    cmdT = "ctest"
testcmd = cmdT + " -V -D Experimental"
# adding parameters
subcmd = ["Start","Test"]
# location of coverage infos
gcnodir = os.path.join(buildDir,"Test","UnitTests","CMakeFiles","optimpp_unit_test.dir")
#gcvor options
gcovrExclusions = ['"(.+/)?Test(.+/)?"','"(.+/)?main.cpp(.+/)?"']
gcovrSources = ['../Test/UnitTests','../Source']
#==================================================
def HaveGcovR():
    if runcommand("gcovr --version") == 0:
        return True
    return False

def HaveCoverageInfos():
    gcno = False
    for root, dirs, files in os.walk(buildDir):
        for file in files:
            if file.endswith(".gcno"):
                gcno = True
                break
        if gcno:
            break
    return gcno

def GetGcovProgram():
    fp = open(os.path.join(buildDir,"CMakeCache.txt"),"r")
    lines = fp.readlines()
    fp.close()
    # search for the used compiler
    Compiler = ""
    for line in lines:
        if not line.startswith("CMAKE_CXX_COMPILER:STRING"):
            continue
        if "clang" in line:
            Compiler = "clang"
            break
        if "g++" in line:
            Compiler = "g++"
            break
    if Compiler == "":
        print("Compiler not supported for coverage analysis")
        return ""
    if Compiler == "g++":
        if shutil.which("egcov"):
            return '"egcov"'
        else:
            return '"gcov"'
    if Compiler == "clang":
        return '"llvm-cov gcov"'
    return ""

#run
def main():
    # ---------------------
    # run the test
    # ---------------------
    os.chdir(buildDir)
    for s in subcmd:
        ret = runcommand(testcmd + s)
        if ret != 0:
            print(" *** /!\\ Error during test run, return code = " + str(ret))
            sys.exit(ret)

    # ---------------------
    # analyse the coverage
    # ---------------------
    gcov = GetGcovProgram()
    if (HaveGcovR() and HaveCoverageInfos() and gcov not in ["",None]):
        # directory change
        os.chdir(buildDir)
        safeRmTree("Coverage")
        os.mkdir("Coverage")
        os.chdir("Coverage")

        # run the coverage
        nbc = getCPUNumber()
        cmd = 'gcovr -v -r  ../../Source -o index.html --html-details -bup '+['--exclude-unreachable-branches',""]["llvm" in gcov]+' --exclude-throw-branches --gcov-executable=' + gcov 
        for ex in gcovrExclusions:
            cmd += ' -e ' +ex
        for sr in gcovrSources:
            cmd += ' ' + sr
        if nbc > 1:
            cmd+=" -j " + str(nbc)
        ret = runcommand(cmd)
        if ret != 0:
            print(" *** /!\\ Error during Coverage analysis, return code = " + str(ret))
            sys.exit(ret)

        # artifact creation
        with zipfile.ZipFile('coverage.zip', 'w') as myzip:
            for file in os.listdir("."):
                if not file.endswith(".html"):
                    continue
                myzip.write(file)
        shutil.move('coverage.zip','../coverage.zip')

        #directory restore
        os.chdir(srcRoot)

    print(" *** return code = " + str(ret))
    sys.exit(ret)

if __name__ == "__main__":
    main()