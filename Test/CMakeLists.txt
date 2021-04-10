
# our project
project(optimpp_unit_test)

file(GLOB
    SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
    )

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
	add_definitions(-Wno-global-constructors)
endif ()

add_executable(optimpp_unit_test ${SRCS})

# base includes
target_include_directories(optimpp_unit_test PUBLIC ${OPTIM_ROOT_DIR}/Source/include)
target_link_libraries(optimpp_unit_test gtest gtest_main optimpplib)

add_test(optimpp_UnitTests ./optimpp_unit_test  --gtest_output=xml:UnitTest_Report.xml --gtest_filter=*:-:*LongTest*)
add_test(optimpp_LongTests ./optimpp_unit_test  --gtest_output=xml:LongTest_Report.xml --gtest_filter=*LongTest*)
set_tests_properties(optimpp_UnitTests PROPERTIES TIMEOUT 3600)
set_tests_properties(optimpp_LongTests PROPERTIES TIMEOUT 10800)
