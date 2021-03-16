# Note: CMake support is community-based. The maintainers do not use CMake
# internally.

cmake_minimum_required(VERSION 2.8.8)

if (POLICY CMP0048)
  cmake_policy(SET CMP0048 NEW)
endif (POLICY CMP0048)

project(googletest-distribution)
set(GOOGLETEST_VERSION 1.10.0)

if (CMAKE_VERSION VERSION_LESS "3.1")
  add_definitions(-std=c++11)
else()
  set(CMAKE_CXX_STANDARD 11)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
  if(NOT CYGWIN)
    set(CMAKE_CXX_EXTENSIONS OFF)
  endif()
endif()

enable_testing()

include(CMakeDependentOption)
include(GNUInstallDirs)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
	add_definitions(
            -Wno-suggest-override
            -Wno-suggest-destructor-override
            -Wno-nonportable-system-include-path
            -Wno-language-extension-token
            -Wno-undef
            -Wno-global-constructors
            -Wno-exit-time-destructors
            -Wno-vla
            -Wno-old-style-cast
            -Wno-covered-switch-default
            -Wno-weak-vtables
            -Wno-switch-enum
            -Wno-used-but-marked-unused
            -Wno-missing-noreturn
            -Wno-vla-extension
            -Wno-shift-sign-overflow
            -Wno-zero-as-null-pointer-constant
            -Wno-unused-member-function
    )
endif ()
#Note that googlemock target already builds googletest
option(BUILD_GMOCK "Builds the googlemock subproject" OFF)
option(INSTALL_GTEST "Enable installation of googletest. (Projects embedding googletest may want to turn this OFF.)" OFF)

if(BUILD_GMOCK)
  add_subdirectory( googlemock )
else()
  add_subdirectory( googletest )
endif()
