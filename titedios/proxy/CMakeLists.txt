cmake_minimum_required (VERSION 3.5.1)
message ("Proxy server")

add_definitions (-std=c++11)

# ========== Proxy ==========
set (COMMON_INC ${CMAKE_CURRENT_SOURCE_DIR}/../include)
set (COMMON_LIB ${CMAKE_CURRENT_SOURCE_DIR}/../library)
set (PROXY_INC ${CMAKE_CURRENT_SOURCE_DIR}/include)
set (PROXY_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src)

include_directories (${COMMON_INC} ${PROXY_INC})
link_directories (${COMMON_LIB})

## ========== unit test ==========
enable_testing()
set (PROXY_SRC_TEST_FILES ${PROXY_SRC}/test_proxy.cc)
add_executable (mini_gw_proxy_test ${PROXY_SRC_TEST_FILES}) 
find_library(GOOGLETEST_LIBRARY gtest gtest_main)
target_link_libraries(mini_gw_proxy_test PUBLIC ${GOOGLETEST_LIBRARY})
add_test (NAME proxy_unit_test
          COMMAND mini_gw_proxy_test
          WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

## ========== operating ==========
set (PROXY_SRC_FILES ${PROXY_SRC}/proxy.cc)
add_executable (mini_gw_proxy ${PROXY_SRC_FILES}) 
target_link_libraries (mini_gw_proxy pthread)

## ========== test client ==========
set (PROXY_SRC_TEST_CLIENT ${PROXY_SRC}/test_client.cc)
add_executable (mini_gw_proxy_test_client ${PROXY_SRC_TEST_CLIENT})
target_link_libraries (mini_gw_proxy_test_client pthread)

## ========== start proxy ==========
add_custom_target (start_proxy
                   COMMAND mini_gw_proxy
                   WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                   DEPENDS mini_gw_proxy)
