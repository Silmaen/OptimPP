# - encoding: UTF-8 -
import sys
from pathlib import Path
from platform import system

SupportedConfiguration = {
    "Windows_clang-native":  {
        "Minimum_version": "11.0",
        "Build_Type":      ["Release", "Debug"],
        "Toolchain":       "CodeBlocks - MinGW Makefiles",
        "C_Compiler":      "C:/Program Files/LLVM/bin/clang.exe",
        "CXX_Compiler":    "C:/Program Files/LLVM/bin/clang++.exe",
    },
    "Windows_clang":         {
        "Minimum_version": "11.0",
        "Build_Type":      ["Release", "Debug"],
        "Toolchain":       "CodeBlocks - MinGW Makefiles",
        "C_Compiler":      "C:/msys64/mingw64/bin/clang.exe",
        "CXX_Compiler":    "C:/msys64/mingw64/bin/clang++.exe",
    },
    "Windows_gcc":           {
        "Minimum_version": "10.0",
        "Build_Type":      ["Release", "Debug"],
        "Toolchain":       "CodeBlocks - MinGW Makefiles",
    },
    "Windows_visual-studio": {
        "Minimum_version":    "19.28",
        "Build_Type":         ["Release", "Debug"],
        "Generator_Platform": "x64",
    },
    "Linux_clang":           {
        "Minimum_version": "10.0",
        "Build_Type":      ["Release", "Debug"],
        "Toolchain":       "Unix Makefiles",
        "C_Compiler":      "/usr/bin/clang",
        "CXX_Compiler":    "/usr/bin/clang++",
    },
    "Linux_gcc":             {
        "Minimum_version": "10.0",
        "Build_Type":      ["Release", "Debug"],
        "Toolchain":       "Unix Makefiles",
        "C_Compiler":      "/usr/bin/gcc",
        "CXX_Compiler":    "/usr/bin/g++",
    },
    "OpenBSD_clang":         {
        "Minimum_version": "10.0",
        "Build_Type":      ["Release", "Debug"],
        "Toolchain":       "Unix Makefiles",
        "C_Compiler":      "/usr/local/bin/clang",
        "CXX_Compiler":    "/usr/local/bin/clang++",
    },
    "OpenBSD_gcc":           {
        "Minimum_version": "10.0",
        "Build_Type":      ["Release", "Debug"],
        "Toolchain":       "Unix Makefiles",
        "C_Compiler":      "/usr/local/bin/egcc",
        "CXX_Compiler":    "/usr/local/bin/eg++",
    }

}

classic_windows_file_path = [
    Path("c:/Program Files/"),
    Path("c:/Program Files (x86)/"),
    Path("c:/msys64/"),
]

log_level = 5


def print_log(msg: str, lvl: int = 1):
    """
    Display a message.
    :param msg: the message
    :param lvl: the message level:
           0 : FATAL ERROR
           1 : ERROR
           2 : WARNING
           3 : REMARK
           4 : STATUS
           5 : DEBUG
    """
    log_levels = ["FATAL ERROR", "ERROR", "WARNING", "REMARK", "", "DEBUG"]
    log_where = [sys.stderr, sys.stderr, sys.stderr, sys.stdout, sys.stdout, sys.stdout]
    print(log_levels[lvl] +  " " + msg, file=log_where[lvl])


def get_supported_os():
    """
    Get the list of supported OS
    :return:
    """
    oss = []
    for key in SupportedConfiguration:
        k = key.split("_")[0]
        if k in oss:
            continue
        oss.append(k)
    return oss


def get_compiler_for_os():
    """
    Get the list of possible compiler for the current OS.
    :return:
    """
    current_os = system()
    compiler_list = []
    for key in SupportedConfiguration:
        o, c = key.split("_", 1)
        if o == current_os:
            compiler_list.append(c)
    return compiler_list


def config_by_compiler(compiler: str):
    """
    Get the Id
    :param compiler:
    :return:
    """
    config = system() + "_" + compiler
    if config in SupportedConfiguration:
        return config
    print_log("Unsupported compiler")
    exit(1)
    return ""


def check_os():
    """
    Check the support of the current os
    :return: True if supported
    """
    return system() in get_supported_os()


src_root = Path(__file__).parent.parent.parent
build_engine = src_root / "Tools" / "BuildEngine"

ActionList = ["clear", "generate", "build", "test", "doc", "package"]
fullActionList = ["All"] + ActionList
doc_build_dir = src_root / "doc" / "build"


def make_output_dir(compiler: str, debug: bool):
    return src_root / ("cmake-build-" + ["release", "debug"][debug] + "-" + compiler)


def zip_folder(zip_file, folder, exclude_patterns=None):
    import os
    if exclude_patterns is None:
        exclude_patterns = []
    for root, dirs, files in os.walk(folder):
        for file in files:
            to_skip = False
            for pat in exclude_patterns:
                if pat in file:
                    to_skip = True
                    break
            if to_skip:
                continue
            zip_file.write(os.path.join(root, file))


def make_scan_build_param(compiler: str, debug: bool):
    scan_build_checkers = [
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
        # "alpha.deadcode.UnreachableCode",
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
        # "apiModeling.StdCLibraryFunctions",
        # "apiModeling.TrustNonnull",
        # "apiModeling.google.GTest",
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
        # "debug.AnalysisOrder",
        # "debug.ConfigDumper",
        # "debug.DumpCFG",
        # "debug.DumpCallGraph",
        # "debug.DumpCalls",
        # "debug.DumpDominators",
        # "debug.DumpLiveStmts",
        # "debug.DumpLiveVars",
        # "debug.DumpTraversal",
        # "debug.ExprInspection",
        # "debug.Stats",
        # "debug.TaintTest",
        # "debug.ViewCFG",
        # "debug.ViewCallGraph",
        # "debug.ViewExplodedGraph",
        "nullability.NullPassedToNonnull",
        "nullability.NullReturnedFromNonnull",
        "nullability.NullableDereferenced",
        "nullability.NullablePassedToNonnull",
        "nullability.NullableReturnedFromNonnull",
        "optin.cplusplus.VirtualCall",
        # "optin.mpi.MPI-Checker",
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
    if "clang" not in compiler.lower():
        print_log("Static analysis only works with clang")
        exit(1)
    opt = SupportedConfiguration[config_by_compiler(compiler)]
    scan_build_param = "-v -k --status-bugs -o " + str(make_output_dir(compiler, debug))
    scan_build_param += " --use-analyzer=" + opt["C_Compiler"]
    scan_build_param += " --use-cc=" + opt["C_Compiler"]
    scan_build_param += " --use-c++=" + opt["CXX_Compiler"]
    scan_build_param += " -enable-checker " + ",".join(scan_build_checkers) + " --exclude Test"
    return scan_build_param


def runcommand(cmd: str):
    """
    Execute safely a system command
    :param cmd: the command to execute
    :return: the return code
    """
    from subprocess import run
    try:
        print_log(">>>" + cmd, 4)
        ret = run(cmd, shell=True).returncode
    except Exception as err:
        print_log("Execution Error: " + str(err))
        ret = -8
    return ret


def run_python(script: str, options: list):
    """
    run a python script
    :param script:
    :param options:
    :return:
    """
    return runcommand(
        "python" + ["", "3"][system() in ["OpenBSD", "Linux"]] + " " + str(script) + " " + " ".join(options))


def get_cpu_number():
    """
    Retrieve the number of CPU of the current machine
    :return: the number of CPU
    """
    try:
        import multiprocessing
        return multiprocessing.cpu_count()
    except (ImportError, NotImplementedError):
        print_log("while finding number of processors")
        return 1


def find_program(program: str, additional_path=None):
    """
    Search for a program
    :param program:
    :param additional_path:
    :return:
    """
    if additional_path is None:
        additional_path = []
    from shutil import which
    to_return = ""
    if which(program) is not None:
        to_return = program
    if system() == "Windows":
        program += ".exe"
    if to_return == "":
        for p in additional_path:
            for pp in p.rglob(program):
                to_return = str(pp)
                break
            if to_return != "":
                break
    if system() == "Windows" and to_return == "":
        for p in classic_windows_file_path:
            for pp in p.rglob(program):
                if pp.is_dir():
                    continue
                to_return = str(pp)
                break
            if to_return != "":
                break
    if to_return == "":
        print_log("could not find " + program + " on this system")
        exit(1)
    if " " in to_return:
        to_return = '"' + to_return + '"'
    return to_return
        elif var_type in ["FILEPATH", "UNINITIALIZED"]:
            if var_val == var_name + "-NOTFOUND":
                cmake_vars[var_name] = None
            else:
                cmake_vars[var_name] = Path(var_val)
        else:
            print_log("Unknown CMakeCache variable type: " + str(var_type) + " in line '" + sline + "'", 2)
            exit(1)
    return cmake_vars
        elif var_type in ["FILEPATH", "UNINITIALIZED"]:
            if var_val == var_name + "-NOTFOUND":
                cmake_vars[var_name] = None
            else:
                cmake_vars[var_name] = Path(var_val)
        else:
            print_log("Unknown CMakeCache variable type: " + str(var_type) + " in line '" + sline + "'", 2)
            exit(1)
    return cmake_vars
