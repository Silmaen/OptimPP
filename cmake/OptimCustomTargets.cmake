
if (CMAKE_BUILD_TYPE MATCHES "Debug")
    set(CONFIG_FLAG "-g")
endif()

# packaging:
add_custom_target(
        Packaging
        COMMAND python "Tools/BuildEngine/packaging.py" "${CONFIG_FLAG}" "-c" "${OPP_COMPILER_NAME}"
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
        COMMENT "Package Application"
        VERBATIM
)
