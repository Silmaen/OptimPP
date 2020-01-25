# - encoding: UTF-8 -
import platform, sys, argparse, subprocess, os, shutil, time, zipfile, copy, datetime

SupportedCompiler = {"Windows":["MSVC","gcc/g++","clang/clang++"],"OpenBSD":["egcc/eg++","clang/clang++"],"Linux":["gcc/g++","clang/clang++"]}
SupportedCompilerShort = {"Windows":["clang","gcc","MSVC"],"OpenBSD":["clang","gcc"],"Linux":["clang","gcc"]}
Corresponding = {
	"WindowsMSVC":"MSVC",
	"Windowsgcc":"gcc/g++",
	"Windowsclang":"clang/clang++",
	"OpenBSDgcc":"egcc/eg++",
	"OpenBSDclang":"clang/clang++",
	"Linuxgcc":"gcc/g++",
	"Linuxclang":"clang/clang++"
}
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
staticanalysisdir=os.path.join(buildDir, "static-analysis")

scanbuildcheckers =[
"alpha.clone.CloneChecker",
"alpha.core.BoolAssignment",
"alpha.core.CallAndMessageUnInitRefArg",
"alpha.core.CastSize",
"alpha.core.CastToStruct",
"alpha.core.Conversion",
"alpha.core.DynamicTypeChecker",
"alpha.core.FixedAddr",
"alpha.core.IdenticalExpr",
"alpha.core.PointerArithm",
"alpha.core.PointerSub",
"alpha.core.SizeofPtr",
"alpha.core.StackAddressAsyncEscape",
"alpha.core.TestAfterDivZero",
"alpha.cplusplus.DeleteWithNonVirtualDtor",
"alpha.cplusplus.EnumCastOutOfRange",
"alpha.cplusplus.InvalidatedIterator",
"alpha.cplusplus.MismatchedIterator",
"alpha.cplusplus.UninitializedObject",
#"alpha.deadcode.UnreachableCode",
"alpha.llvm.Conventions",
"alpha.security.ArrayBound",
"alpha.security.ArrayBoundV2",
"alpha.security.MallocOverflow",
"alpha.security.MmapWriteExec",
"alpha.security.ReturnPtrRange",
"alpha.security.taint.TaintPropagation",
"alpha.unix.BlockInCriticalSection",
"alpha.unix.Chroot",
"alpha.unix.PthreadLock",
"alpha.unix.SimpleStream",
"alpha.unix.Stream",
"alpha.unix.cstring.BufferOverlap",
"alpha.unix.cstring.NotNullTerminated",
"alpha.unix.cstring.OutOfBounds",
#"apiModeling.StdCLibraryFunctions",
#"apiModeling.TrustNonnull",
#"apiModeling.google.GTest",
"core.CallAndMessage",
"core.DivideZero",
"core.DynamicTypePropagation",
"core.NonNullParamChecker",
"core.NonnilStringConstants",
"core.NullDereference",
"core.StackAddressEscape",
"core.UndefinedBinaryOperatorResult",
"core.VLASize",
"core.builtin.BuiltinFunctions",
"core.builtin.NoReturnFunctions",
"core.uninitialized.ArraySubscript",
"core.uninitialized.Assign",
"core.uninitialized.Branch",
"core.uninitialized.CapturedBlockVariable",
"core.uninitialized.UndefReturn",
"cplusplus.InnerPointer",
"cplusplus.Move",
"cplusplus.NewDelete",
"cplusplus.NewDeleteLeaks",
"cplusplus.SelfAssignment",
"deadcode.DeadStores",
#"debug.AnalysisOrder",
#"debug.ConfigDumper",
#"debug.DumpCFG",
#"debug.DumpCallGraph",
#"debug.DumpCalls",
#"debug.DumpDominators",
#"debug.DumpLiveStmts",
#"debug.DumpLiveVars",
#"debug.DumpTraversal",
#"debug.ExprInspection",
#"debug.Stats",
#"debug.TaintTest",
#"debug.ViewCFG",
#"debug.ViewCallGraph",
#"debug.ViewExplodedGraph",
"nullability.NullPassedToNonnull",
"nullability.NullReturnedFromNonnull",
"nullability.NullableDereferenced",
"nullability.NullablePassedToNonnull",
"nullability.NullableReturnedFromNonnull",
"optin.cplusplus.VirtualCall",
#"optin.mpi.MPI-Checker",
"optin.performance.GCDAntipattern",
"optin.performance.Padding",
"optin.portability.UnixAPI",
"security.FloatLoopCounter",
"security.insecureAPI.UncheckedReturn",
"security.insecureAPI.bcmp",
"security.insecureAPI.bcopy",
"security.insecureAPI.bzero",
"security.insecureAPI.getpw",
"security.insecureAPI.gets",
"security.insecureAPI.mkstemp",
"security.insecureAPI.mktemp",
"security.insecureAPI.rand",
"security.insecureAPI.strcpy",
"security.insecureAPI.vfork",
"unix.API",
"unix.Malloc",
"unix.MallocSizeof",
"unix.MismatchedDeallocator",
"unix.Vfork",
"unix.cstring.BadSizeArg",
"unix.cstring.NullArg",
"valist.CopyToSelf",
"valist.Uninitialized",
"valist.Unterminated",
]

ScanbuildParam="-v -k --use-analyzer=/usr/local/bin/clang --use-cc=/usr/local/bin/clang --use-c++=/usr/local/bin/clang++  --status-bugs -o " + staticanalysisdir
ScanbuildParam+=" -enable-checker " + ",".join(scanbuildcheckers) + " --exclude Test"

PytonExe = "python"
if OS in ["OpenBSD"]:
    PytonExe+="3"

if os.getcwd() != srcRoot:
    #print("WARNING: not in the source's root directory",file=sys.stderr)
    os.chdir(srcRoot)


# ==============================================================================
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

# ==============================================================================
def runcommandWithOutPut(cmd:str):
    try:
        print(">>>"+cmd)
        retour = subprocess.run(cmd,
                     shell = True,
                     stdout= subprocess.PIPE,
                     stderr=subprocess.STDOUT,
                     text=os.linesep)
        ret = retour.returncode
        output = retour.stdout.split(os.linesep)
    except:
        output = ["error in command"]
        ret = -6
    return ret,output;

# ==============================================================================
def runcommand(cmd:str):
    try:
        print(">>>"+cmd)
        ret = subprocess.run(cmd, shell = True, stdout = sys.stdout, stderr = sys.stderr).returncode
    except:
        print("error in command")
        ret = -8
    return ret;

# ==============================================================================
def runPython(pythonscript:str,params:list):
    try:
        cmd = PytonExe + " " + pythonscript + " " + " ".join(params)
    except:
        print("bad Python command")
        return -87
    return runcommand(cmd)

# ==============================================================================
def getCPUNumber():
    try:
        import multiprocessing
        return multiprocessing.cpu_count()
    except (ImportError, NotImplementedError):
        print("Error while finding number of processors")
        return 1

# ==============================================================================
def getCMakeProgram():
    # definition of the CMake command
    if OS == "Windows":
        return '"C:\\Program Files\\CMake\\bin\\cmake.exe"'
    else:
        return "cmake"

# ==============================================================================
def endCommand(ret):
	os.chdir(srcRoot)
	print(" *** return code = " + str(ret) )
	sys.exit(ret)
