cmake_minimum_required (VERSION 3.5.1)
project ("Internal API server")

if (NOT MSVC)
  add_definitions (-std=c++11)
else ()
  add_definitions (-D_WIN32_WINNT=0x600)
endif()

# interal API server
set (COMMON_INC ${CMAKE_CURRENT_SOURCE_DIR}/../include)
set (COMMON_LIB ${CMAKE_CURRENT_SOURCE_DIR}/../library)
set (IAS_INC ${CMAKE_CURRENT_SOURCE_DIR}/include)
set (IAS_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src)

include_directories (${COMMON_INC} ${IAS_INC})
link_directories (${COMMON_LIB})

## ========== unit test ==========
enable_testing()
set (IAS_SRC_TEST_FILES ${IAS_SRC}/test_internal_API_server.cc)
add_executable (test_internal_API_server ${IAS_SRC_TEST_FILES}) 
find_library(GOOGLETEST_LIBRARY gtest gtest_main)
target_link_libraries(test_internal_API_server PUBLIC ${GOOGLETEST_LIBRARY})
add_test (NAME ias_unit_test
          COMMAND test_internal_API_server
          WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

## ========== operating ==========
set (IAS_SRC_FILES ${IAS_SRC}/internal_API_server.cc)
add_executable (internal_API_server ${IAS_SRC_FILES}) 
target_link_libraries (internal_API_server pthread)

## ========== start proxy ==========
add_custom_target (start_ias
                   COMMAND internal_API_server
                   WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                   DEPENDS internal_API_server)

## ========== cpp rest test ==========
find_package (Boost REQUIRED COMPONENTS program_options regex)
include_directories (${Boost_INCLUDE_DIRS})
#find_package(cpprestsdk REQUIRED NAMES cpprestsdk cpprest)
find_package(cpprestsdk REQUIRED)

add_executable (test_cpp_rest ${IAS_SRC}/my_server.cc ${IAS_SRC}/my_server_main.cc) 

target_link_libraries(test_cpp_rest PUBLIC ${cpprestsdk} pthread ${Boost_LIBRARIES})
