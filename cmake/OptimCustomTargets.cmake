
if (CMAKE_BUILD_TYPE MATCHES "Debug")
    set(CONFIG_FLAG "-g")
endif()

find_program(ZIP_BIN zip PATHS ${OPP_COMPILER_PATH} ${OPP_ADDITIONAL_PATH})

if (NOT ZIP_BIN)
    message(FATAL_ERROR "zip executable not found! Aborting.")
endif()

add_custom_command(TARGET Documentation
        # Run after all other rules within the target have been executed
        POST_BUILD
        COMMAND cd ${CMAKE_SOURCE_DIR}/doc/build/html && ${ZIP_BIN} -r ../documentation.zip *
        COMMENT "Post Doxygen generation: zip the result"
        VERBATIM
        )

if (ENABLE_CODE_COVERAGE)
    add_custom_command(TARGET test-and-coverage
            # Run after all other rules within the target have been executed
            POST_BUILD
            COMMAND cd ${CMAKE_COVERAGE_OUTPUT_DIRECTORY} && ${ZIP_BIN} -r ${CMAKE_BINARY_DIR}/coverage.zip *
            COMMENT "Post coverage generation: zip the result"
            VERBATIM
            )
endif()

# packaging:
add_custom_target(
        Packaging
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/documentation
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/doc/build/html ${CMAKE_BINARY_DIR}/documentation
        COMMAND cd ${CMAKE_BINARY_DIR} &&  ${ZIP_BIN} -r optimpp.zip bin lib documentation
        COMMENT "Package Application"
        VERBATIM
        DEPENDS optimpp Documentation
)
