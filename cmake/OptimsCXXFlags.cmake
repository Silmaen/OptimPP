################################################ TECHNODIGIT ##############################################
## This file is part of the 3DReshaper technology software and is a proprietary information of TECHNODIGIT.
## Do NOT reproduce or disclose this file without TECHNODIGIT written consent.
###########################################################################################################


###############################################################################
## 3DReshaper common CXX flags
###############################################################################

# Defining helper variables
if (MSVC) # MSVC
	set(OPP_COMPILER_MSVC ON)
elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang") # Clang
	set(OPP_COMPILER_CLANG ON)
elseif (CMAKE_CXX_COMPILER_ID MATCHES "GNU") # GCC
	set(OPP_COMPILER_GCC ON)
endif ()

if (WIN32 OR CYGWIN)
	set(OPP_PLATFORM_WINDOWS ON)
elseif (APPLE)
	set(OPP_PLATFORM_MAC ON)
elseif (UNIX)
	set(OPP_PLATFORM_LINUX ON)
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
