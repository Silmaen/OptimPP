
# Code coverage option (only in debug under linux)
option(ENABLE_CODE_COVERAGE "Enable generation of coverage data (only in debug)" OFF)

find_program(LLVM_COV_PATH llvm-cov PATHS ${OPP_COMPILER_PATH} ${OPP_ADDITIONAL_PATH})
find_program(LLVM_PROFDATA_PATH llvm-profdata PATHS ${OPP_COMPILER_PATH} ${OPP_ADDITIONAL_PATH})
find_program(GCOVR_PATH gcovr ${OPP_COMPILER_PATH} ${OPP_ADDITIONAL_PATH})

message("OPP_COMPILER_PATH: ${OPP_COMPILER_PATH}")
message("LLVM_COV_PATH: ${LLVM_COV_PATH}")
message("LLVM_PROFDATA_PATH: ${LLVM_PROFDATA_PATH}")
message("GCOVR_PATH: ${GCOVR_PATH}")


# Variables
set(CMAKE_COVERAGE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Coverage)

if (ENABLE_CODE_COVERAGE AND NOT CODE_COVERAGE_ADDED)
    set(CODE_COVERAGE_ADDED ON)

    if(NOT GCOVR_PATH)
        message(FATAL_ERROR "Unable to find gcovr executable")
    endif()

    add_custom_target(
            coverage-clean
            COMMAND ${CMAKE_COMMAND} -E remove_directory
            ${CMAKE_COVERAGE_OUTPUT_DIRECTORY})
    add_custom_target(
            coverage-preprocessing
            COMMAND ${CMAKE_COMMAND} -E make_directory
            ${CMAKE_COVERAGE_OUTPUT_DIRECTORY}
            DEPENDS coverage-clean)


    if(OPP_COMPILER_CLANG)
        # Messages
        message(STATUS "Building with llvm Code Coverage Tools")

        if(NOT LLVM_COV_PATH)
            message(FATAL_ERROR "llvm-cov not found! Aborting.")
        endif()

        add_compile_options(-fprofile-arcs -ftest-coverage -fno-inline)
        add_link_options(--coverage)
        set(OPP_COVERAGE_COMMAND "${LLVM_COV_BIN}" )
        set(OPP_GCOVR_ADD_OPTIONS "--exclude-unreachable-branches" )
        set(OPP_GCOV ${LLVM_COV_PATH})
    elseif(OPP_COMPILER_GCC)
        # Messages
        message(STATUS "Building with lcov Code Coverage Tools")
        if(CMAKE_BUILD_TYPE)
            if(NOT ${CMAKE_BUILD_TYPE_UPPER} STREQUAL "DEBUG")
                message(WARNING "Code coverage results with an optimized (non-Debug) build may be misleading")
            endif()
        else()
            message(WARNING "Code coverage results with an optimized (non-Debug) build may be misleading")
        endif()

        add_compile_options(--coverage -fprofile-arcs -ftest-coverage -fno-inline -fno-inline-small-functions -fno-default-inline)
        link_libraries(gcov)
        set(OPP_COVERAGE_COMMAND "gcov" )
        find_program(OPP_GCOV gcov ${OPP_COMPILER_PATH} ${OPP_ADDITIONAL_PATH})
    else()
        message(FATAL_ERROR "Code coverage requires Clang or GCC. Aborting.")
    endif()

    set(OPP_GCOVR_EXCLUDES "-e \"(.+/)?Test(.+/)?\" -e \"(.+/)?main.cpp(.+/)?\"")


    add_custom_target(
            coverage-processing
            COMMAND ${GCOVR_PATH} -v -r \"${CMAKE_SOURCE_DIR}\" -o index.html --html-details -bup
                    ${OPP_GCOVR_ADD_OPTIONS} --exclude-throw-branches --gcov-executable=\"${OPP_GCOV}\"
                    ${OPP_GCOVR_EXCLUDES}
            WORKING_DIRECTORY ${CMAKE_COVERAGE_OUTPUT_DIRECTORY}
            DEPENDS testing_run coverage-preprocessing
    )
endif()
