
if (CMAKE_BUILD_TYPE MATCHES "Debug")
    set(CONFIG_FLAG "-g")
endif()

# packaging:
add_custom_target(
        Packaging
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/documentation
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/doc/build/html ${CMAKE_BINARY_DIR}/documentation
        COMMAND cd ${CMAKE_BINARY_DIR} &&  zip -r optimpp.zip bin lib documentation
        COMMENT "Package Application"
        VERBATIM
        DEPENDS optimpp Documentation
)
