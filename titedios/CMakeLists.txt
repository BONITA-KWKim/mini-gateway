cmake_minimum_required (VERSION 2.8)
project (mini_gateway)
message (${CMAKE_PROJECT_NAME})

add_definitions (-std=c++11)

set (SRC ${CMAKE_CURRENT_SOURCE_DIR}/src)
set (INC ${CMAKE_CURRENT_SOURCE_DIR}/include)
set (LIB ${CMAKE_CURRENT_SOURCE_DIR}/library)
include_directories (${INC})
link_directories(${LIB})

set (SRC_FILES ${SRC}/test.cc)
add_executable (mini_gw_test ${SRC_FILES})
target_link_libraries(mini_gw_test gtest)
