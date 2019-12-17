cmake_minimum_required (VERSION 3.5.1)
project ("Internal API server")

if (NOT MSVC)
  add_definitions (-std=c++11)
else ()
  add_definitions (-D_WIN32_WINNT=0x600)
endif()

# interal API server
set (IAS_INC ${CMAKE_CURRENT_SOURCE_DIR}/include)
set (IAS_LIB ${CMAKE_CURRENT_SOURCE_DIR}/library)
set (IAS_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src)
set (IAS_BIN ${CMAKE_CURRENT_SOURCE_DIR}/bin)

## operating
set (IAS_SRC_FILES ${IAS_SRC}/internal_API_server.cc)
add_executable (internal_API_server ${IAS_SRC_FILES}) 
target_include_directories (internal_API_server PUBLIC ${IAS_INC})
target_link_libraries (internal_API_server pthread)

## TARGETS
set (TEST_IAS_SRC_FILES ${IAS_SRC}/test_internal_API_server.cc)
add_executable (test_internal_API_server ${TEST_IAS_SRC_FILES}) 
target_include_directories (test_internal_API_server PUBLIC ${IAS_INC})
target_link_directories (test_internal_API_server PUBLIC ${IAS_LIB})
target_link_libraries (test_internal_API_server gtest)

## installation
install (TARGETS internal_API_server test_internal_API_server
         RUNTIME DESTINATION ${IAS_BIN})
