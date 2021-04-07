
set(INT_THIRD_PARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(THIRD_PARTY_DIR ${INT_THIRD_PARTY_DIR} PARENT_SCOPE)

set(JSON_INCLUDE_DIR ${INT_THIRD_PARTY_DIR}/nlohmann PARENT_SCOPE)

if (MSVC)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()
add_subdirectory(GoogleTest)
if (MSVC)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()
