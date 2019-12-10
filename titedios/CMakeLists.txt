cmake_minimum_required (VERSION 2.8)
project (mini_gateway)
message (${CMAKE_PROJECT_NAME})

set (SRC ./src)
set (INC ./include)
set (SRC_FILES SRC/test.cc)
include_directories (${INC})
add_executable (app.out ${SRC_FILES})