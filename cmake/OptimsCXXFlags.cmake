# Defining helper variables
if (MSVC) # MSVC
	if (CMAKE_CXX_COMPILER_ID MATCHES "Clang") # Clang
		set(OPP_COMPILER_CLANG ON)
		message(STATUS "** Compiler detected Clang-cl")
		message(FATAL-ERROR "Clang-cl for msvc build is not supported.")
	else()
		set(OPP_COMPILER_MSVC ON)
		message(STATUS "** Compiler detected MSVC")
	endif()
elseif (CMAKE_CXX_COMPILER_ID MATCHES "(Apple)?[Cc]lang") # Clang
	set(OPP_COMPILER_CLANG ON)
	message(STATUS "** Compiler detected Clang")
elseif (CMAKE_CXX_COMPILER_ID MATCHES "GNU") # GCC
	set(OPP_COMPILER_GCC ON)
	message(STATUS "** Compiler detected GCC")
endif ()

if (WIN32 OR CYGWIN)
	set(OPP_PLATFORM_WINDOWS ON)
	message(STATUS "** Platform detected Windows")
elseif (APPLE)
	set(OPP_PLATFORM_MAC ON)
elseif (CMAKE_SYSTEM_NAME MATCHES "Linux")
	message(STATUS "** Platform detected Mac")
elseif (UNIX)
	set(OPP_PLATFORM_LINUX ON)
elseif (CMAKE_SYSTEM_NAME MATCHES "OpenBSD")
	set(OPP_PLATFORM_OBSD ON)
	message(STATUS "** Platform detected Linux")
endif ()

if (OPP_COMPILER_MSVC)
	set(OPP_CONFIG_DEBUG "$<IF:$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>,ON,OFF>")
	set(OPP_CONFIG_RELEASE "$<IF:$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>,OFF,ON>")

	set(OPP_CONFIG_SHORT "$<IF:$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>,Debug,Release>")
else ()
	if (CMAKE_BUILD_TYPE MATCHES "(D|d)eb")
		set(OPP_CONFIG_DEBUG ON)
		set(OPP_CONFIG_SHORT "Debug")
	else ()
		set(OPP_CONFIG_RELEASE OFF)
		set(OPP_CONFIG_SHORT "Release")
	endif ()
endif ()

if (OPP_COMPILER_GCC)
	set(
		OPP_CXX_FLAGS_COMMON

		-Wall
		-Wextra
		-Werror

	)
elseif (OPP_COMPILER_CLANG)
	set(
		OPP_CXX_FLAGS_COMMON

		-pedantic
		-pedantic-errors
		-Weverything
		-Werror
		-Wno-c++98-compat
		-Wno-c++98-compat-pedantic
		-Wno-padded
	)
	if (OPP_PLATFORM_LINUX)
	  set(
		OPP_CXX_FLAGS_COMMON

		${OPP_CXX_FLAGS_COMMON}
		-Wno-disabled-macro-expansion
		)
	endif()

	# Handling warnings available since Clang 8
	if (CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 8)
		set(
			OPP_CXX_FLAGS_COMMON

			${OPP_CXX_FLAGS_COMMON}
		)
	endif ()
elseif (OPP_COMPILER_MSVC)
	set(
		OPP_CXX_FLAGS_COMMON

		/W4
		/WX # Treat warnings as errors
		/permissive-
	)

	# Replacing /W[0-4] flag(s) by /W4, to avoid conflicting warning levels
	if (CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
		string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	endif ()
endif ()

# Replacing ';' by a space, since setting values automatically inserts ';' between each element
string(REPLACE ";" " " OPP_CXX_FLAGS_COMMON "${OPP_CXX_FLAGS_COMMON}")

# Enable the debug Windows macro in Debug build type
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG")

get_filename_component(COMPILER_PATH ${CMAKE_CXX_COMPILER} DIRECTORY)

# Allowing to enable clang-tidy if compiling with Clang
if (OPP_COMPILER_CLANG)
	option(ENABLE_CLANG_TIDY "Enable clang-tidy" OFF)

	if (ENABLE_CLANG_TIDY)
		set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # To produce compilation commands to be used by clang-tidy

		if (OPP_PLATFORM_WINDOWS)
			set(CLANG_TIDY_EXECUTABLE "${CMAKE_HOME_DIRECTORY}/Tools/clang/clang-tidy.exe")
		else ()
			set(CLANG_TIDY_EXECUTABLE "clang-tidy")
		endif ()

		set(
			CMAKE_CXX_CLANG_TIDY

			"${CLANG_TIDY_EXECUTABLE}"
			-p "${CMAKE_BINARY_DIR}"
		)
	endif ()
endif ()

include(c++-standards)
cxx_17()
