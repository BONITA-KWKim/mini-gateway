cmake_minimum_required (VERSION 3.5.1)
message ("Proxy server")

add_definitions (-std=c++11)

# Proxy
set (PROXY_INC ${CMAKE_CURRENT_SOURCE_DIR}/include)
set (PROXY_LIB ${CMAKE_CURRENT_SOURCE_DIR}/library)
set (PROXY_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src)
set (PROXY_BIN ${CMAKE_CURRENT_SOURCE_DIR}/bin)

#[[
## unit test
set (PROXY_SRC_TEST_FILES ${PROXY_SRC}/test_proxy.cc)
add_executable (mini_gw_proxy_test ${PROXY_SRC_TEST_FILES}) 
target_include_directories (mini_gw_proxy_test PUBLIC ${PROXY_INC})
target_link_directories (mini_gw_proxy_test PUBLIC ${PROXY_LIB})
target_link_libraries (mini_gw_proxy_test gtest)
]]

## operating
set (PROXY_SRC_FILES ${PROXY_SRC}/proxy.cc)
add_executable (mini_gw_proxy ${PROXY_SRC_FILES}) 
target_include_directories (mini_gw_proxy PUBLIC ${PROXY_INC})
target_link_libraries (mini_gw_proxy pthread)

## test client
set (PROXY_SRC_TEST_CLIENT ${PROXY_SRC}/test_client.cc)
add_executable (mini_gw_proxy_test_client ${PROXY_SRC_TEST_CLIENT})
target_link_libraries (mini_gw_proxy_test_client pthread)

## installation
#install (TARGETS mini_gw_proxy mini_gw_proxy_test_client mini_gw_proxy_test 
#         RUNTIME DESTINATION ${PROXY_BIN})
install (TARGETS mini_gw_proxy mini_gw_proxy_test_client 
         RUNTIME DESTINATION ${PROXY_BIN})
