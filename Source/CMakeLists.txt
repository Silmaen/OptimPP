
# our project
project(optimpp)

file(
	GLOB
	SRCS
	
	${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/source/*/*.cpp
)

file(GLOB
    LOCAL_INCLUDES
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*/*.h
    )

add_library(optimpplib ${SRCS} ${LOCAL_INCLUDES})
target_include_directories(optimpplib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/)


add_executable(optimpp ${CMAKE_CURRENT_SOURCE_DIR}/source/main.cpp)
target_link_libraries(optimpp optimpplib)

target_include_directories(optimpp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/)


