
# Code coverage option (only in debug under linux)
option(ENABLE_CODE_COVERAGE "Enable generation of coverage data (only in debug)" OFF)

find_program(LLVM_COV_PATH llvm-cov PATHS ${OPP_COMPILER_PATH} ${OPP_ADDITIONAL_PATH})
find_program(LLVM_PROFDATA_PATH llvm-profdata PATHS ${OPP_COMPILER_PATH} ${OPP_ADDITIONAL_PATH})
find_program(LCOV_PATH lcovPATHS  ${OPP_COMPILER_PATH} ${OPP_ADDITIONAL_PATH})
find_program(GENHTML_PATH genhtml PATHS ${OPP_COMPILER_PATH} ${OPP_ADDITIONAL_PATH})

message("OPP_COMPILER_PATH: ${OPP_COMPILER_PATH}")
message("LLVM_COV_PATH: ${LLVM_COV_PATH}")
message("LLVM_PROFDATA_PATH: ${LLVM_PROFDATA_PATH}")
message("LCOV_PATH: ${LCOV_PATH}")
message("GENHTML_PATH: ${GENHTML_PATH}")

# Hide behind the 'advanced' mode flag for GUI/ccmake
mark_as_advanced(FORCE LLVM_COV_PATH LLVM_PROFDATA_PATH LCOV_PATH GENHTML_PATH)

# Variables
set(CMAKE_COVERAGE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Coverage)

if (ENABLE_CODE_COVERAGE AND NOT CODE_COVERAGE_ADDED)
    set(CODE_COVERAGE_ADDED ON)

    # Common Targets
    add_custom_target(
            coverage-preprocessing
            COMMAND ${CMAKE_COMMAND} -E make_directory
            ${CMAKE_COVERAGE_OUTPUT_DIRECTORY}
            DEPENDS coverage-clean)

    if(CMAKE_C_COMPILER_ID MATCHES "(Apple)?[Cc]lang"
            OR CMAKE_CXX_COMPILER_ID MATCHES "(Apple)?[Cc]lang")
        # Messages
        message(STATUS "Building with llvm Code Coverage Tools")

        if(NOT LLVM_COV_PATH)
            message(FATAL_ERROR "llvm-cov not found! Aborting.")
        else()
            # Version number checking for 'EXCLUDE' compatibility
            execute_process(COMMAND ${LLVM_COV_PATH} --version
                    OUTPUT_VARIABLE LLVM_COV_VERSION_CALL_OUTPUT)
            string(REGEX MATCH "[0-9]+\\.[0-9]+\\.[0-9]+" LLVM_COV_VERSION
                    ${LLVM_COV_VERSION_CALL_OUTPUT})

            if(LLVM_COV_VERSION VERSION_LESS "10.0.0")
                message(
                        WARNING
                        "target_code_coverage()/add_code_coverage_all_targets() 'EXCLUDE' option only available on llvm-cov >= 10.0.0"
                )
            endif()
        endif()
        # Targets
        add_custom_target(
                coverage-clean
                COMMAND rm -f ${CMAKE_COVERAGE_OUTPUT_DIRECTORY}/binaries.list
                COMMAND rm -f ${CMAKE_COVERAGE_OUTPUT_DIRECTORY}/profraw.list)

        # Used to get the shared object file list before doing the main all-
        # processing
        add_custom_target(
                coverage-libs
                COMMAND ;
                COMMENT "libs ready for coverage report.")
    elseif(CMAKE_C_COMPILER_ID MATCHES "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU")
        # Messages
        message(STATUS "Building with lcov Code Coverage Tools")

        if(CMAKE_BUILD_TYPE)
            string(TOUPPER ${CMAKE_BUILD_TYPE} upper_build_type)
            if(NOT ${upper_build_type} STREQUAL "DEBUG")
                message(WARNING "Code coverage results with an optimized (non-Debug) build may be misleading")
            endif()
        else()
            message(WARNING "Code coverage results with an optimized (non-Debug) build may be misleading")
        endif()
        if(NOT LCOV_PATH)
            message(FATAL_ERROR "lcov not found! Aborting...")
        endif()
        if(NOT GENHTML_PATH)
            message(FATAL_ERROR "genhtml not found! Aborting...")
        endif()

        # Targets
        add_custom_target(
                coverage-clean COMMAND
                ${LCOV_PATH} --directory
                ${CMAKE_BINARY_DIR} --zerocounters)

    else()
        message(FATAL_ERROR "Code coverage requires Clang or GCC. Aborting.")
    endif()
endif()

if (0)
    if (CMAKE_BUILD_TYPE MATCHES "Debug")
        if (ENABLE_CODE_COVERAGE)
            set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")
            if (OPP_COMPILER_GCC)
                set(OPP_CXX_FLAGS_COVERAGE "--coverage -fprofile-arcs -ftest-coverage -fno-inline -fno-inline-small-functions -fno-default-inline")
            elseif (OPP_COMPILER_CLANG)
                set(OPP_CXX_FLAGS_COVERAGE "-fprofile-arcs -ftest-coverage -fno-inline") # -fprofile-instr-generate -fcoverage-mapping
                set(CMAKE_EXE_LINKER_FLAGS "--coverage")# -fprofile-instr-generate

                message(STATUS " $$$ CMAKE_CXX_COMPILER: ${CMAKE_CXX_COMPILER}")
                message(STATUS " $$$ COMPILER_PATH: ${COMPILER_PATH}")
                find_program(LLVM_COV_BIN "llvm-cov" PATHS ${COMPILER_PATH})
                message(STATUS " $$$ LLVM_COV_BIN: ${LLVM_COV_BIN}")
                if (LLVM_COV_BIN)
                    set(COVERAGE_COMMAND "${LLVM_COV_BIN}" )
                    message(STATUS " $$$ COVERAGE_COMMAND: ${COVERAGE_COMMAND}")
                    find_program(LLVM_COV_WRAPPER "llvm-cov-wrapper" PATHS ${CMAKE_MODULE_PATH})
                    message(STATUS " $$$ LLVM_COV_WRAPPER: ${LLVM_COV_WRAPPER}")
                    if (LLVM_COV_WRAPPER)
                        set(COVERAGE_COMMAND "${LLVM_COV_WRAPPER}" CACHE FILEPATH "")
                    endif ()
                endif ()
            else()
                message(ERROR Compiler not supported for coverage)
            endif ()
            message(STATUS " ** coverage enabled with ${COVERAGE_COMMAND}" )
            set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${OPP_CXX_FLAGS_COVERAGE}")
        endif ()
    endif ()
endif ()