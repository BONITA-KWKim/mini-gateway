cmake_minimum_required (VERSION 2.8)
project (mini_gateway)
message (${CMAKE_PROJECT_NAME})

add_definitions (-std=c++11)

# build proxy server
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/proxy)

# build internal API server
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/internal-API-server)
