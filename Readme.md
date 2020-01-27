# Optim++ #

Open source Shape Computation Program and mathematics

## Prerequisits ##

for build ding the solution on any platform, here are the needed components

### supported Paltform ###

The build has been tested on

 * Windows 10
 * OpenBSD 6.6
 * Linux Ubuntu 19.10

### packages ###

 * Python >= 3.7
 * cmake >= 3.10
 * GCC >= 8 or Clang >= 8 or (windows only) MSVC 2019
 * LLVM > 8 (for static analysis)
 * gcov (or llvm-cov) 
 * gcovr >= 4.2 (/!\ for windows users, see the modification to add bellow)
 * doxygen >= 1.8.10
 * graphviz >= 2.36.0

### gcovr and Windows users ###

A small bug exists while using llvm-cov throug gcovr: if using "--perserve-path" in llvm-cov gcov commang the include files are not well formed.
you need to edit the file '<PythonLibDir>/site-packages/gcovr/gcov.py' to modify function 'run_gcov_and_process_files' (line 633 in v4.2):

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

to get the help about the BuildingEngine and all possible option just type:

```
python Tools/BuildingEngine.py -h
```

