
if (CMAKE_BUILD_TYPE MATCHES "Debug")
    set(CONFIG_FLAG "-g")
endif()

# testing + coverage:
add_custom_target(
        Test_and_coverage
        COMMAND python "Tools/BuildEngine/runtest.py" "${CONFIG_FLAG}" "-c" "${OPP_COMPILER_NAME}"
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
        COMMENT "Package Application"
        VERBATIM
)

# packaging:
add_custom_target(
        Packaging
        COMMAND python "Tools/BuildEngine/packaging.py" "${CONFIG_FLAG}" "-c" "${OPP_COMPILER_NAME}"
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
        COMMENT "Package Application"
        VERBATIM
)
