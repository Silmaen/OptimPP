# need a recent CMAKE
cmake_minimum_required(VERSION 3.10.0)

# our project
project(Optim++)

set(OPTIM_ROOT_DIR   "${PROJECT_SOURCE_DIR}")

set(CMAKE_INSTALL_PREFIX ${PROJECT_BUILD_DIR}/Install)

set(CMAKE_CXX_STANDARD 17)

if (CMAKE_SYSTEM_NAME MATCHES "OpenBSD") 

elseif (CMAKE_SYSTEM_NAME MATCHES "Windows") 

else()
    message( FATAL_ERROR "Unsupported Operating System '${CMAKE_SYSTEM_NAME}'" )
endif()


# subproject TEST
add_subdirectory(Source)

enable_testing()

# subproject TEST
add_subdirectory(Test)
## CTEST SUPPORT ----------------------------------------------------
include(CTest)
