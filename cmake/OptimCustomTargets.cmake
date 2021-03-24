
if (CMAKE_BUILD_TYPE MATCHES "Debug")
    set(CONFIG_FLAG "-g")
endif()

# packaging:
add_custom_target(
        Packaging
        COMMAND ;
        COMMENT "Package Application"
        VERBATIM
)
