cmake_minimum_required (VERSION 3.5.1)
message ("internal message server")

if (NOT MSVC)
  add_definitions (-std=c++11)
else ()
  add_definitions (-D_WIN32_WINNT=0x600)
endif()

# interal message server
set (COMMON_INC ${CMAKE_CURRENT_SOURCE_DIR}/../include)
set (COMMON_LIB ${CMAKE_CURRENT_SOURCE_DIR}/../library)
set (IMS_INC ${CMAKE_CURRENT_SOURCE_DIR}/include)
set (IMS_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src)

set (IMS_ATALK ${IMS_SRC}/atalk)
set (IMS_FTALK ${IMS_SRC}/ftalk)
set (IMS_MMS ${IMS_SRC}/mms)
set (IMS_SMS ${IMS_SRC}/sms)
set (IMS_TXT_MODULE ${IMS_SRC}/text-message-modules)

include_directories (${COMMON_INC} ${IMS_INC})
link_directories (${COMMON_LIB})

## ========== find packages =========
find_package(GTest REQUIRED)
find_package (Boost REQUIRED COMPONENTS system program_options regex)
find_library (openssl REQUIRED)
find_library (cpprest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})
include_directories (${Boost_INCLUDE_DIRS})

## ========== operating ==========
set (IMS_TEST_MODULES ${IMS_SRC}/IMS_test.cc)
set (IMS_TXT_MSG_MODULES ${IMS_TXT_MODULE}/parser.cc)
set (IMS_HTTPS_MODULES ${IMS_ATALK}/IMS_atalk.cc ${IMS_FTALK}/IMS_ftalk.cc 
                        ${IMS_MMS}/IMS_mms.cc ${IMS_SMS}/IMS_sms.cc)
set (IMS_SRC_FILES ${IMS_SRC}/internal_message_server_main.cc
                   ${IMS_HTTPS_MODULES} ${IMS_TXT_MSG_MODULES} ${IMS_TEST_MODULES})

add_executable (internal_message_server ${IMS_SRC_FILES}) 
target_link_libraries (internal_message_server PUBLIC cpprest pthread ssl 
                       crypto ${Boost_LIBRARIES})

## ========== unit test ==========
enable_testing()
set (IMS_SRC_TEST_FILES ${IMS_SRC}/test_internal_message_server.cc)

add_executable (test_internal_message_server ${IMS_SRC_TEST_FILES}
                ${IMS_VENDOR_MODULES} ${IMS_TEST_MODULES}) 
target_link_libraries(test_internal_message_server PUBLIC cpprest pthread 
                      ssl crypto ${Boost_LIBRARIES} 
                      GTest::GTest GTest::Main)

add_test (NAME IMS_unit_test
          COMMAND test_internal_message_server
          WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

## ========== start proxy ==========
add_custom_target (start_IMS
                   COMMAND internal_message_server
                   WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                   DEPENDS internal_message_server)

#========== test request ==========
add_executable (test_request ${IMS_SRC}/test_request.cc) 
target_link_libraries(test_request PUBLIC cpprest pthread ssl crypto ${Boost_LIBRARIES})
