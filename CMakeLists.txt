# need a recent CMAKE
cmake_minimum_required(VERSION 3.10.0)

# our project
project(Optim++)

set(OPTIM_ROOT_DIR   "${PROJECT_SOURCE_DIR}")
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
if (${OPTIM_ROOT_DIR} STREQUAL ${PROJECT_BINARY_DIR})
    message(FATAL_ERROR "You cannot run CMake in the source directory, please create a dedicated build directory (take a look at the README).")
endif()

# Set the common compiler flags
message(STATUS "Setup the compilation flags")
include("OptimsCXXFlags")

# set the C++ standard that we use
# note that setting the CMAKE_CXX_STANDARD variable to 17 to generate a Visual Studio solution is supported by CMake version 3.10.0 or above.

if (OPP_COMPILER_GCC)
	if (NOT CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 7.0)
		message(FATAL_ERROR "Error: GCC 7.0 or above is needed")
	endif ()
elseif(OPP_COMPILER_CLANG)
	if (NOT CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 6.0)
		message(FATAL_ERROR "Error: Clang 6.0 or above is needed")
	endif ()
elseif (OPP_COMPILER_MSVC)
	if (NOT MSVC_VERSION GREATER_EQUAL "1914")
		message(FATAL_ERROR "Error: MSVC 19.14 or above is needed")
	endif ()
endif ()

set(CMAKE_CXX_STANDARD 17)

# Set a default build type if none was specified
# Documentation link: https://blog.kitware.com/cmake-and-the-default-build-type/
# This is not applicable to MSVC since all 4 configurations are available inside the VS solution
if (NOT OPP_COMPILER_MSVC)
	message(STATUS "------------- The CXX compiler identification is ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")

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

message(STATUS "CMAKE_BUILD_TYPE = ${CMAKE_BUILD_TYPE}")

message(STATUS "The CXX compiler identification is ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")

set(CMAKE_INSTALL_PREFIX ${PROJECT_BUILD_DIR}/Install)

# Affectation of CXX flags for the different configurations
foreach (cfg "DEBUG" "RELEASE" "MINSIZEREL" "RELWITHDEBINFO")
	set (CMAKE_CXX_FLAGS_${cfg} "${CMAKE_CXX_FLAGS_${cfg}} ${OPP_CXX_FLAGS_COMMON}")
endforeach ()

# ---------------------------------------------------------------------------
# Code Coverage (in Debug Mode only)
# https://gronlier.fr/blog/2015/01/adding-code-coverage-to-your-c-project/
# ---------------------------------------------------------------------------
if (NOT OPP_COMPILER_MSVC)
	if (CMAKE_BUILD_TYPE MATCHES "Debug")
		# common setting to gcc and clang
		set(OPP_CXX_FLAGS_COVERAGE "--coverage -g -O0 ")

		if (OPP_COMPILER_GCC)
			set(OPP_CXX_FLAGS_COVERAGE "-fprofile-arcs -ftest-coverage -fno-inline -fno-inline-small-functions -fno-default-inline")
		endif ()

		# set Clang specif object flags
		if (OPP_COMPILER_CLANG)
			set(OPP_CXX_FLAGS_COVERAGE "-fprofile-arcs -ftest-coverage -fno-inline -fprofile-instr-generate -fcoverage-mapping")
			set(CMAKE_EXE_LINKER_FLAGS "--coverage -fprofile-instr-generate")

			find_program(LLVM_COV_BIN "llvm-cov" PATHS ${COMPILER_PATH})
			if (LLVM_COV_BIN)
				find_program(LLVM_COV_WRAPPER "llvm-cov-wrapper" PATHS ${CMAKE_MODULE_PATH})
				if (LLVM_COV_WRAPPER)
					set(COVERAGE_COMMAND "${LLVM_COV_WRAPPER}" CACHE FILEPATH "")
				endif ()
			endif ()
		endif ()

		set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${OPP_CXX_FLAGS_COVERAGE}")
	endif ()
endif ()

# Display the compilation flags
if (NOT OPP_COMPILER_MSVC)
	string(TOUPPER ${CMAKE_BUILD_TYPE} CMAKE_BUILD_TYPE_UPPER)
	message(STATUS "Compilation flags: CMAKE_CXX_FLAGS_${CMAKE_BUILD_TYPE_UPPER} = ${CMAKE_CXX_FLAGS_${CMAKE_BUILD_TYPE_UPPER}}")
endif ()

enable_testing()

# subproject TEST
add_subdirectory(Source)

# subproject TEST
add_subdirectory(Test)
## CTEST SUPPORT ----------------------------------------------------
include(CTest)
