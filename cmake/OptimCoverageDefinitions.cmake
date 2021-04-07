
# Code coverage option (only in debug under linux)
option(ENABLE_CODE_COVERAGE "Enable generation of coverage data (only in debug)" OFF)

find_program(LLVM_COV_PATH llvm-cov PATHS ${OPP_COMPILER_PATH} ${OPP_ADDITIONAL_PATH} NO_DEFAULT_PATH )
find_program(GCOV_PATH gcov ${OPP_COMPILER_PATH} ${OPP_ADDITIONAL_PATH})

set(OPP_GCOVR_CMD python ${OPTIM_ROOT_DIR}/Tools/gcovr.py)

# Variables
set(CMAKE_COVERAGE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Coverage)

if (ENABLE_CODE_COVERAGE AND NOT CODE_COVERAGE_ADDED)
    set(CODE_COVERAGE_ADDED ON)

    if(OPP_COMPILER_CLANG)
        if (CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 11.0)

            # Messages
            message(STATUS "Building with llvm Code Coverage Tools")

            if(NOT LLVM_COV_PATH)
                message(FATAL_ERROR "llvm-cov not found! Aborting.")
            endif()

            add_compile_options(--coverage -O0)
            add_link_options(--coverage -O0)
            set(OPP_COVERAGE_COMMAND "${LLVM_COV_PATH} gcov")
        else()
            set(ENABLE_CODE_COVERAGE OFF)
            message(STATUS Code coverage deactivated)
        endif()
    elseif(OPP_COMPILER_GCC)
        # Messages
        message(STATUS "Building with gcov Code Coverage Tools")
        if(CMAKE_BUILD_TYPE)
            if(NOT ${CMAKE_BUILD_TYPE_UPPER} STREQUAL "DEBUG")
                message(WARNING "Code coverage results with an optimized (non-Debug) build may be misleading")
            endif()
        else()
            message(WARNING "Code coverage results with an optimized (non-Debug) build may be misleading")
        endif()

        add_compile_options(--coverage -O0 -fPIC -fno-inline)
        add_link_options(--coverage -O0)
        #link_libraries(gcov)
        set(OPP_COVERAGE_COMMAND "${GCOV_PATH}")
    else()
        message(FATAL_ERROR "Code coverage requires Clang or GCC. Aborting.")
    endif()
endif()

if (ENABLE_CODE_COVERAGE)

    if (CMAKE_VERBOSE_MAKEFILE)
        set(GCOVR_VERBOSITY "-v")
    endif()
    add_custom_target(
            test-and-coverage
            COMMAND ${CMAKE_COMMAND} -E remove *.gcda;
            COMMAND ${CMAKE_COMMAND} -E remove *.gcno;
            COMMAND $<TARGET_FILE:optimpp_unit_test> "--gtest_output=xml:test/UnitTest_Report.xml" "--gtest_filter=*:-:*LongTest*"
            COMMAND $<TARGET_FILE:optimpp_unit_test> "--gtest_output=xml:test/LongTest_Report.xml" "--gtest_filter=*LongTest*"
            COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_COVERAGE_OUTPUT_DIRECTORY}
            COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_COVERAGE_OUTPUT_DIRECTORY}/*
            COMMAND cd ${CMAKE_COVERAGE_OUTPUT_DIRECTORY} &&
            ${OPP_GCOVR_CMD} ${GCOVR_VERBOSITY} -r \"${CMAKE_SOURCE_DIR}\" -o index.html
            --html-details --html-details-syntax-highlighting --html-title \"${CMAKE_CXX_COMPILER_ID} Code Coverage Report\"
            -bpd --gcov-ignore-parse-error
            --gcov-executable=${OPP_COVERAGE_COMMAND}
            --exclude-throw-branches
            -e \"\(.+/\)?Test\(.+/\)?\"
            -e \"\(.+/\)?3rdParty\(.+/\)?\"
            -e \"\(.+/\)?main.cpp\(.+/\)?\"
            DEPENDS optimpp_unit_test
    )

else()
    add_custom_target(
            test-and-coverage
            COMMAND $<TARGET_FILE:optimpp_unit_test> "--gtest_output=xml:test/UnitTest_Report.xml" "--gtest_filter=*:-:*LongTest*"
            COMMAND $<TARGET_FILE:optimpp_unit_test> "--gtest_output=xml:test/LongTest_Report.xml" "--gtest_filter=*LongTest*"
            DEPENDS optimpp_unit_test
    )
endif()
