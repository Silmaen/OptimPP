
add_custom_target(
        Documentation
        COMMAND python "Tools/BuildEngine/documentation.py"
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/.."
        COMMENT "Generate documentation"
        VERBATIM
)
