
add_custom_target(
        Documentation
        COMMAND python "Tools/BuildEngine/Documentation.py"
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/.."
        COMMENT "Generate documentation"
        VERBATIM
)
