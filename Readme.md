# Optim++ #

Open source Shape Computation Program and mathematics

## Prerequisits ##

For build ding the solution on any platform, here are the needed components

### Supported Paltform ###

The build has been tested on

 * Windows 10
 * OpenBSD 6.8
 * Linux

### Packages ###

 * Python >= 3.7
 * cmake >= 3.10
 * GCC >= 8 or Clang >= 10 or (windows only) MSVC 2019
 * LLVM > 10 (for static analysis)
 * gcov and llvm-cov
 * doxygen >= 1.9.10
 * graphviz >= 2.36.0

### gcovr and Windows users ###

The optim++ comes with it embedded version of gcovr.

If one want to use a release of gcovr, on Windows with gcovr version 4.2, a small bug exists 
while using llvm-cov through gcovr: if using `--perserve-path` in `llvm-cov gcov` command, it 
generates include files not well-formed.

You need to edit the file '<PythonLibDir>/site-packages/gcovr/gcov.py' to amend function 'run_gcov_and_process_files' (line 633 in v4.2):

```python
def run_gcov_and_process_files(
        abs_filename, covdata, options, logger, error, toerase, chdir, tempdir):
    # If the first element of cmd - the executable name - has embedded spaces
    # it probably includes extra arguments.
    cmd = options.gcov_cmd.split(' ') + [
            abs_filename,
            "--branch-counts", "--branch-probabilities"]
    if "Windows" not in platform.system() or "llvm"  not in options.gcov_cmd:
        # problem with preservce path on windows llvm-cov
        cmd += ["--preserve-paths"]
    cmd += ['--object-directory', os.path.dirname(abs_filename)]
```

## Building the source ##

If all requirement are satisfied, just go into the sources root directory then use the building engine:

```
python Tools/BuildingEngine.py All
```

To get the help about the BuildingEngine and all possible option just type:

```
python Tools/BuildingEngine.py -h
```

