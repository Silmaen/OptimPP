#!/usr/bin/env python3
# - encoding: UTF-8 -
import shutil
import sys
from argparse import ArgumentParser
from copy import deepcopy
from pathlib import Path
from platform import system

src_root = Path(__file__).absolute().parent.parent
ActionList2 = ["clear", "generate", "build", "test", "doc", "StaticAnalysis", "package"]
classic_windows_file_path = [
    Path("c:/Program Files/"),
    Path("c:/Program Files (x86)/"),
    Path("c:/msys64/"),
]
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
    print(log_levels[lvl] + " " + msg, file=log_where[lvl])


def make_output_dir(compiler: str, debug: bool):
    return src_root / ("cmake-build-" + ["release", "debug"][debug] + "-" + compiler)


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


def gogo(cmake_path, compiler, debug, options):
    build_dir = make_output_dir(compiler, debug)
    cmd = [cmake_path]
    cmd += [' -S "' + str(src_root.absolute()) + '"', ' -B "' + str(build_dir.absolute()) + '"']
    cmd += [" -DCMAKE_BUILD_TYPE=" + ["Release", "Debug"][debug]]
    for key in options:
        if key in ["Minimum_version", "Build_Type"]:
            continue
        if key == "Toolchain":
            cmd += [' -G "' + options[key] + '"']
            continue
        cmd += [" -DCMAKE_" + key.upper() + '="' + options[key] + '"']
    if debug and compiler in ["gcc", "clang"]:
        cmd += [" -DENABLE_CODE_COVERAGE=ON"]
    return cmd


def do_action(action, compiler, debug):
    build_dir = make_output_dir(compiler, debug)
    cmake_path = find_program("cmake")
    options = SupportedConfiguration[config_by_compiler(compiler)]
    nbc = get_cpu_number()
    if action == "clear":
        shutil.rmtree(build_dir, ignore_errors=True)
        build_dir.mkdir(parents=True, exist_ok=True)
    elif action == "generate":
        cmd = gogo(cmake_path, compiler, debug, options)
        return runcommand(" ".join(cmd))
    elif action == "build":
        cmd = [cmake_path, "--build " + str(build_dir.absolute())]
        if nbc > 1:
            cmd += [" -j "+str(nbc)]
        return runcommand(" ".join(cmd))
    elif action == "test":
        cmd = [cmake_path, "--build " + str(build_dir.absolute()), "-t test-and-coverage"]
        if nbc > 1:
            cmd += [" -j "+str(nbc)]
        return runcommand(" ".join(cmd))
    elif action == "doc":
        cmd = [cmake_path, "--build " + str(build_dir.absolute()), "-t Documentation"]
        if nbc > 1:
            cmd += [" -j "+str(nbc)]
        return runcommand(" ".join(cmd))
    elif action == "StaticAnalysis":
        if system() == "Windows":
            scb = 'perl -S "C:/Program Files/LLVM/bin/scan-build"'
        else:
            scb = find_program("scan-build")
        cmd = gogo(cmake_path, "clang", True, options)
        ret = runcommand(" ".join(cmd))
        if ret != 0:
            return ret
        cmd = [scb, make_scan_build_param("clang", True), cmake_path, " --build " + str(build_dir.absolute()), "-j" + str(nbc)]
        return runcommand(" ".join(cmd))
    elif action == "package":
        cmd = [cmake_path, "--build " + str(build_dir.absolute()), "-t Packaging"]
        if nbc > 1:
            cmd += [" -j "+str(nbc)]
        return runcommand(" ".join(cmd))
    else:
        return 1
    return 0


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


def main():
    print("*************************** " + str(src_root) + " ************************************")
    parser = ArgumentParser()
    parser.add_argument(
        "action",
        nargs='+',
        choices=ActionList2,
        help="what to do"
    )
    compilers = get_compiler_for_os()
    parser.add_argument(
        "-c", "--compiler",
        type=str,
        choices=compilers,
        default=compilers[0],
        help="The compiler to be used")
    parser.add_argument(
        "-g", "--debug",
        action="store_true",
        help="If we should compile in Debug mode"
    )
    parser.add_argument(
        "-s", "--staticAnalysis",
        action="store_true",
        help="If we should do the static analysis"
    )
    args = parser.parse_args()
    # Filling up the action list
    todo = []
    if "All" in args.action:
        todo = deepcopy(ActionList2)
    else:
        for a in ActionList2:
            if a in args.action:
                todo.append(a)
        # Execute the list of action
    for action in todo:
        ret = do_action(action, args.compiler, args.debug)
        if ret != 0:
            exit(ret)

    # Final message
    print_log("Everything ends up quite well!", 4)


if __name__ == "__main__":
    main()
