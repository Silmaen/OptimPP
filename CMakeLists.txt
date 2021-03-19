# How to use
#
#   $ # assuming in reshaper source code root folder
#   $ mkdir build           # create a new folder where the compiled stuff will be create
#   $ cd build              # change to this folder
#   $ cmake ..              # use CMake to constuct the makefile
#   $ make -j 8             # build 3D Reshaper
#   $ ctest                 # run all tests (output will be a summary)
#   $  # run Rsh Geometry google tests
#
# To force CMake to use GCC and Debug mode
#   $ cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ ..
#
# To force CMake to use Clang:
#   $ cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ ..
#   $ cmake -DCMAKE_BUILD_TYPE=Debug   -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ ..
#
# To perform memory checking (and excluding long test)
#   $ cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ ..
#   $ make -j 8
#   $ ctest -T MemCheck --exclude-regex "LongTest"
#
# To perform code coverage
#   $ cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ ..
#   $ make -j 8
#   $ ctest -T Coverage --exclude-regex "LongTest"
#
# To perform code coverage and publish result
#   $ cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ ..
#   $ make -j 8
#   $ ctest -D Experimental
#
# To run Header verification
#   $ cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ ..
#   $ make RshGeometryHeaderVerification
#

# Min version = 3.12 to use add_compile_definitions
cmake_minimum_required(VERSION 3.10.0)

# our project
project(Optim++)

set(OPTIM_ROOT_DIR   "${PROJECT_SOURCE_DIR}")
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set(CMAKE_VERBOSE_MAKEFILE OFF)

if (${OPTIM_ROOT_DIR} STREQUAL ${PROJECT_BINARY_DIR})
    message(FATAL_ERROR "You cannot run CMake in the source directory, please create a dedicated build directory (take a look at the README).")
endif()

include("OptimConfig")

# set the C++ standard that we use
# note that setting the CMAKE_CXX_STANDARD variable to 17 to generate a Visual Studio solution is supported by CMake version 3.10.0 or above.
cxx_17()

if (OPP_COMPILER_GCC)
	if (NOT CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL ${OPP_GCC_MINIMAL})
		message(FATAL_ERROR "Error: GCC ${OPP_GCC_MINIMAL} or above is needed")
	endif ()
elseif(OPP_COMPILER_CLANG)
	if (NOT CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL ${OPP_CLANG_MINIMAL})
		message(FATAL_ERROR "Error: Clang ${OPP_CLANG_MINIMAL} or above is needed")
	endif ()
elseif (OPP_COMPILER_MSVC)
	if (NOT MSVC_VERSION GREATER_EQUAL ${OPP_MSVC_MINIMAL})
		message(FATAL_ERROR "Error: MSVC ${OPP_CLANG_MINIMAL} or above is needed")
	endif ()
endif ()

# Set a default build type if none was specified
# Documentation link: https://blog.kitware.com/cmake-and-the-default-build-type/
# This is not applicable to MSVC since all 4 configurations are available inside the VS solution
if (NOT OPP_COMPILER_MSVC)
	set(default_build_type "Release")

	if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
		message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
		set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE
		    STRING "Choose the type of build." FORCE)

		# Set the possible values of build type for cmake-gui
		set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
		             "Debug" "Release" "RelWithDebInfo" "MinSizeRel")
	endif ()

	if (NOT CMAKE_BUILD_TYPE MATCHES "^(Debug|Release|RelWithDebInfo|MinSizeRel)$")
		message(FATAL_ERROR "Invalid Configuration type: ${CMAKE_BUILD_TYPE}
		                    CMAKE_BUILD_TYPE must be Debug, Release, RelWithDebInfo or MinSizeRel
		                    For example: cmake -DCMAKE_BUILD_TYPE=Debug .."
		)
	endif ()
endif ()

message(">>> CMAKE_BUILD_TYPE = ${CMAKE_BUILD_TYPE}")
message(">>> The OS identification is ${CMAKE_SYSTEM} ${CMAKE_SYSTEM_NAME}")
message(">>> The CXX compiler identification is ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")

# Affectation of CXX flags for the different configurations
foreach (cfg "DEBUG" "RELEASE" "MINSIZEREL" "RELWITHDEBINFO")
	set (CMAKE_CXX_FLAGS_${cfg} "${CMAKE_CXX_FLAGS_${cfg}} ${OPP_CXX_FLAGS_COMMON}")
endforeach ()

include("OptimCoverageDefinitions")
include("OptimSanitizersDefinitions")

# Display the compilation flags
message(STATUS "Compilation flags: CMAKE_CXX_FLAGS_${CMAKE_BUILD_TYPE_UPPER} = ${CMAKE_CXX_FLAGS_${CMAKE_BUILD_TYPE_UPPER}}")
message(STATUS "Linking  flags   : CMAKE_EXE_LINKER_FLAGS = ${CMAKE_EXE_LINKER_FLAGS}")

enable_testing()

# subproject Source
add_subdirectory(Source)

# subproject Test
add_subdirectory(Test)

# subproject Documentation
add_subdirectory(doc)

include("OptimCustomTargets")

## CTEST SUPPORT ----------------------------------------------------
include(CTest)
