
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
        COMMAND ${ZIP_BIN} -r ../documentation.zip *
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/doc/build/html
        COMMENT "Post Doxygen generation: zip the result"
        )

if (ENABLE_CODE_COVERAGE)
    add_custom_command(TARGET test-and-coverage
            # Run after all other rules within the target have been executed
            POST_BUILD
            COMMAND ${ZIP_BIN} -r ${CMAKE_BINARY_DIR}/coverage.zip *
            WORKING_DIRECTORY ${CMAKE_COVERAGE_OUTPUT_DIRECTORY}
            COMMENT "Post coverage generation: zip the result"
            )

endif()

# packaging:
add_custom_target(
        Packaging
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/documentation
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/doc/build/html ${CMAKE_BINARY_DIR}/documentation
        COMMAND ${ZIP_BIN} -r optimpp.zip bin lib documentation
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Package Application"
        DEPENDS optimpp Documentation
)
