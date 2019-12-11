cmake_minimum_required (VERSION 2.8)
project (mini_gateway)
message (${CMAKE_PROJECT_NAME})

add_definitions (-std=c++11)

# Global
set (INC ${CMAKE_CURRENT_SOURCE_DIR}/include)
set (LIB ${CMAKE_CURRENT_SOURCE_DIR}/library)
set (BIN ${CMAKE_CURRENT_SOURCE_DIR}/bin)
include_directories (${INC})
link_directories (${LIB})

# main
set (SRC ${CMAKE_CURRENT_SOURCE_DIR}/src)
set (SRC_FILES ${SRC}/test.cc)
add_executable (mini_gw_test ${SRC_FILES})
target_link_libraries (mini_gw_test gtest)

# Proxy
set (PROXY_INC ${CMAKE_CURRENT_SOURCE_DIR}/gw-proxy/include)
set (PROXY_SRC ${CMAKE_CURRENT_SOURCE_DIR}/gw-proxy/src)
set (PROXY_SRC_TEST_FILES ${PROXY_SRC}/test_proxy.cc)
set (PROXY_SRC_FILES ${PROXY_SRC}/proxy.cc)
## unit test
add_executable (mini_gw_proxy_test ${PROXY_SRC_TEST_FILES}) 
target_include_directories (mini_gw_proxy_test PUBLIC ${PROXY_INC})
target_link_libraries (mini_gw_proxy_test gtest)
## operating
add_executable (mini_gw_proxy ${PROXY_SRC_FILES}) 
target_include_directories (mini_gw_proxy PUBLIC ${PROXY_INC})
target_link_libraries (mini_gw_proxy pthread)
## test client
set (PROXY_SRC_TEST_CLIENT ${PROXY_SRC}/test_client.cc)
add_executable (mini_gw_proxy_test_client ${PROXY_SRC_TEST_CLIENT})
target_link_libraries (mini_gw_proxy_test_client pthread)