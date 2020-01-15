cmake_minimum_required (VERSION 3.5.1)
project ("Internal message server")

if (NOT MSVC)
  add_definitions (-std=c++11)
else ()
  add_definitions (-D_WIN32_WINNT=0x600)
endif()

# interal message server
set (COMMON_INC ${CMAKE_CURRENT_SOURCE_DIR}/../include)
set (COMMON_LIB ${CMAKE_CURRENT_SOURCE_DIR}/../library)
set (IAS_INC ${CMAKE_CURRENT_SOURCE_DIR}/include)
set (IAS_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src)

include_directories (${COMMON_INC} ${IAS_INC})
link_directories (${COMMON_LIB})

## ========== find packages =========
find_package(GTest REQUIRED)
find_package (Boost REQUIRED COMPONENTS system program_options regex)
find_library (openssl REQUIRED)
find_library (cpprest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})
include_directories (${Boost_INCLUDE_DIRS})

## ========== unit test ==========
enable_testing()
set (IAS_SRC_TEST_FILES ${IAS_SRC}/test_internal_message_server.cc)
add_executable (test_internal_message_server ${IAS_SRC_TEST_FILES}) 
target_link_libraries(test_internal_message_server PUBLIC cpprest pthread 
                      ssl crypto ${Boost_LIBRARIES} 
                      GTest::GTest GTest::Main)

add_test (NAME ias_unit_test
          COMMAND test_internal_message_server
          WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

## ========== operating ==========
set (IAS_SRC_FILES ${IAS_SRC}/internal_message_server.cc ${IAS_SRC}/internal_message_server_main.cc)
add_executable (internal_message_server ${IAS_SRC_FILES}) 
target_link_libraries (internal_message_server PUBLIC cpprest pthread ssl 
                       crypto ${Boost_LIBRARIES})

## ========== start proxy ==========
add_custom_target (start_ias
                   COMMAND internal_message_server
                   WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                   DEPENDS internal_message_server)

#========== test request ==========
add_executable (test_request ${IAS_SRC}/test_request.cc) 
target_link_libraries(test_request PUBLIC cpprest pthread ssl crypto ${Boost_LIBRARIES})
