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
if (${OPTIM_ROOT_DIR} STREQUAL ${PROJECT_BINARY_DIR})
    message(FATAL_ERROR "You cannot run CMake in the source directory, please create a dedicated build directory (take a look at the README).")
endif()

# Set the common compiler flags
message(STATUS ">>> Setup the compilation flags")
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

message(STATUS ">>> CMAKE_BUILD_TYPE = ${CMAKE_BUILD_TYPE}")
message(STATUS ">>> The OS identification is ${CMAKE_SYSTEM} ${CMAKE_SYSTEM_NAME}")
message(STATUS ">>> The CXX compiler identification is ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")

include("OptimDefinitions")

set(CMAKE_INSTALL_PREFIX ${PROJECT_BUILD_DIR}/Install)

# Affectation of CXX flags for the different configurations
foreach (cfg "DEBUG" "RELEASE" "MINSIZEREL" "RELWITHDEBINFO")
	set (CMAKE_CXX_FLAGS_${cfg} "${CMAKE_CXX_FLAGS_${cfg}} ${OPP_CXX_FLAGS_COMMON}")
endforeach ()
# Sanitizers
option(ENABLE_ADDRESS_SANITIZER "Enable AddressSanitizer (only in debug under linux)" OFF)
option(ENABLE_UNDEFINED_BEHAVIOR_SANITIZER "Enable UndefinedBehavior (only in debug under linux)" OFF)

# Code coverage option (only in debug under linux)
option(ENABLE_CODE_COVERAGE "Enable generation of coverage data (only in debug)" OFF)

if (NOT OPP_COMPILER_MSVC)
	if (CMAKE_BUILD_TYPE MATCHES "Debug")
		if (ENABLE_CODE_COVERAGE)
			
			set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")
			if (OPP_COMPILER_GCC)
				set(OPP_CXX_FLAGS_COVERAGE "--coverage -fprofile-arcs -ftest-coverage -fno-inline -fno-inline-small-functions -fno-default-inline")
			endif ()

			if (OPP_COMPILER_CLANG)
				set(OPP_CXX_FLAGS_COVERAGE "-fprofile-arcs -ftest-coverage -fno-inline") # -fprofile-instr-generate -fcoverage-mapping
				set(CMAKE_EXE_LINKER_FLAGS "--coverage")# -fprofile-instr-generate

				#find_program(LLVM_COV_BIN "llvm-cov" PATHS ${COMPILER_PATH})
				#if (LLVM_COV_BIN)
				#	find_program(LLVM_COV_WRAPPER "llvm-cov-wrapper" PATHS ${CMAKE_MODULE_PATH})
				#	if (LLVM_COV_WRAPPER)
				#		set(COVERAGE_COMMAND "${LLVM_COV_WRAPPER}" CACHE FILEPATH "")
				#	endif ()
				#endif ()
			endif ()

			set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${OPP_CXX_FLAGS_COVERAGE}")
		endif ()
		set(SANITIZER_COUNT 0)
		if (ENABLE_ADDRESS_SANITIZER)
			MATH(EXPR SANITIZER_COUNT "${SANITIZER_COUNT}+1")
			set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address -O0 -g3 -fno-omit-frame-pointer -fno-optimize-sibling-calls")
		endif ()
		if (ENABLE_THREAD_SANITIZER)
			MATH(EXPR SANITIZER_COUNT "${SANITIZER_COUNT}+1")
			set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=thread -O0 -g3 -fno-omit-frame-pointer -fno-optimize-sibling-calls")
		endif ()
		if (ENABLE_MEMORY_SANITIZER)
			MATH(EXPR SANITIZER_COUNT "${SANITIZER_COUNT}+1")
			set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=memory -O0 -g3 -fno-omit-frame-pointer -fno-optimize-sibling-calls")
		endif ()
		if (ENABLE_UNDEFINED_BEHAVIOR_SANITIZER)
			MATH(EXPR SANITIZER_COUNT "${SANITIZER_COUNT}+1")
			set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=undefined -O0 -g3 -fno-omit-frame-pointer -fno-optimize-sibling-calls")
		endif ()
		if (ENABLE_DATA_FLOW_SANITIZER)
			MATH(EXPR SANITIZER_COUNT "${SANITIZER_COUNT}+1")
			set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=dataflow -O0 -g3 -fno-omit-frame-pointer -fno-optimize-sibling-calls")
		endif ()
		if (ENABLE_CONTROL_FLOW_INTEGRITY_SANITIZER)
			MATH(EXPR SANITIZER_COUNT "${SANITIZER_COUNT}+1")
			set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=cfi -flto -O0 -g3 -fno-omit-frame-pointer -fno-optimize-sibling-calls")
		endif ()
		if (ENABLE_SAFE_STACK_SANITIZER)
			MATH(EXPR SANITIZER_COUNT "${SANITIZER_COUNT}+1")
			set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=safe-stack -O0 -g3 -fno-omit-frame-pointer -fno-optimize-sibling-calls")
		endif ()

		if (SANITIZER_COUNT GREATER 1)
			message(FATAL_ERROR "You can only use sanitizers one by one.")
		endif ()
	endif ()
endif ()

# Display the compilation flags
if (NOT OPP_COMPILER_MSVC)
	string(TOUPPER ${CMAKE_BUILD_TYPE} CMAKE_BUILD_TYPE_UPPER)
	message(STATUS "Compilation flags: CMAKE_CXX_FLAGS_${CMAKE_BUILD_TYPE_UPPER} = ${CMAKE_CXX_FLAGS_${CMAKE_BUILD_TYPE_UPPER}}")
endif ()
set(CMAKE_VERBOSE_MAKEFILE ON)
message(STATUS "Compilation flags: CMAKE_CXX_FLAGS_${CMAKE_BUILD_TYPE_UPPER} = ${CMAKE_CXX_FLAGS_${CMAKE_BUILD_TYPE_UPPER}}")
message(STATUS "Linking  flags   : CMAKE_EXE_LINKER_FLAGS = ${CMAKE_EXE_LINKER_FLAGS}")

enable_testing()

# subproject Source
add_subdirectory(Source)

# subproject Test
add_subdirectory(Test)

# subproject Documentation
add_subdirectory(doc)

if (CMAKE_BUILD_TYPE MATCHES "Debug")
	set(LCONFIG "-g")
endif()


message(STATUS "CMAKE_BUILD_TYPE_UPPER: ${CMAKE_BUILD_TYPE_UPPER}")
message(STATUS "CMAKE_BINARY_DIR: ${CMAKE_BINARY_DIR}")

string(TOLOWER ${CMAKE_BUILD_TYPE} CMAKE_BUILD_TYPE_LOWER)

get_filename_component(CONF_NAME ${CMAKE_BINARY_DIR} NAME)
string(REPLACE "cmake-build-${CMAKE_BUILD_TYPE_LOWER}-" "" COMPILER_NAME ${CONF_NAME})

message(STATUS "COMPILER_NAME: ${COMPILER_NAME}")
message(STATUS "LCONFIG: ${LCONFIG}")

# packaging:
add_custom_target(
		Packaging
		COMMAND python "Tools/BuildEngine/packaging.py" "${LCONFIG}" "-c" "${COMPILER_NAME}"
		WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
		COMMENT "Package Application"
		VERBATIM
)


## CTEST SUPPORT ----------------------------------------------------
include(CTest)
