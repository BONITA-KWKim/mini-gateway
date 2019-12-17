cmake_minimum_required (VERSION 3.5.1)
project (mini_gateway)

add_definitions (-std=c++11)

# build proxy server
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/proxy)

# build internal API server
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/internal-API-server)
