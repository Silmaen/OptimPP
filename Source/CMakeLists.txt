
# our project
project(optimpp)

file(
	GLOB
	SRCS

	${CMAKE_CURRENT_SOURCE_DIR}/source/*/*.cpp
)

file(GLOB
    LOCAL_INCLUDES
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*/*.h
    )

# TODO: make this shared also for windows!
if (OPP_PLATFORM_WINDOWS)
	add_library(optimpplib ${SRCS} ${LOCAL_INCLUDES})
else ()
	add_library(optimpplib ${SRCS} ${LOCAL_INCLUDES})
endif ()

target_include_directories(optimpplib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/)

set_target_properties(optimpplib
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    PDB_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

if (NOT MSVC)
	# Deleting all the potentially remaining .gcda files (used for code coverage)
	#add_custom_command(TARGET optimpplib PRE_BUILD COMMAND find ${CMAKE_CURRENT_BINARY_DIR} -iname "*.gcda" -delete)
endif ()

add_executable(optimpp ${CMAKE_CURRENT_SOURCE_DIR}/source/main.cpp)
target_include_directories(optimpp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/)
target_link_libraries(optimpp optimpplib)

set_target_properties(optimpp
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    PDB_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

