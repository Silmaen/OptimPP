# Defining helper variables
if (MSVC) # MSVC
	if (CMAKE_CXX_COMPILER_ID MATCHES "(Apple)?[Cc]lang") # Clang
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
	if (CMAKE_CXX_COMPILER_VERSION LESS 9.0)
		message(STATUS "** Old GCC found")
		link_libraries(stdc++fs)
	endif()
endif ()

if (WIN32 OR CYGWIN)
	set(OPP_PLATFORM_WINDOWS ON)
	message(STATUS "** Platform detected Windows")
elseif (APPLE)
	set(OPP_PLATFORM_MAC ON)
	message(STATUS "** Platform detected Mac")
elseif (CMAKE_SYSTEM_NAME MATCHES "Linux")
	set(OPP_PLATFORM_LINUX ON)
	message(STATUS "** Platform detected Linux")
elseif (UNIX)
	set(OPP_PLATFORM_LINUX ON)
	message(STATUS "** Platform detected unix")
elseif (CMAKE_SYSTEM_NAME MATCHES "OpenBSD")
	set(OPP_PLATFORM_OBSD ON)
	message(STATUS "** Platform detected OpenBSD")
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
		-pedantic
		-pedantic-errors
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
get_filename_component(COMPILER_PATH ${CMAKE_CXX_COMPILER} DIRECTORY)

include(c++-standards)
cxx_17()
