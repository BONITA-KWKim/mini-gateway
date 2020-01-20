cmake_minimum_required (VERSION 3.5.1)
message ("db manager")

if (NOT MSVC)
  add_definitions (-std=c++11)
else ()
  add_definitions (-D_WIN32_WINNT=0x600)
endif()

# interal message server
set (COMMON_INC ${CMAKE_CURRENT_SOURCE_DIR}/../include)
set (COMMON_LIB ${CMAKE_CURRENT_SOURCE_DIR}/../library)
set (DB_M_INC ${CMAKE_CURRENT_SOURCE_DIR}/include)
set (DB_M_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src)

include_directories (${COMMON_INC} ${DB_M_INC})
link_directories (${COMMON_LIB})

## ========== find packages =========
find_package(GTest REQUIRED)
find_package (Boost REQUIRED COMPONENTS system program_options regex)
find_library (openssl REQUIRED)
find_library (cpprest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})
include_directories (${Boost_INCLUDE_DIRS})

## ========== operating ==========
set (DB_M_SRC_FILES ${DB_M_SRC}/db-manager-main.cc)

add_executable (db-manager ${DB_M_SRC_FILES}) 
target_link_libraries (db-manager PUBLIC pthread ${Boost_LIBRARIES})

## ========== unit test ==========
enable_testing()
set (DB_M_SRC_TEST_FILES ${DB_M_SRC}/test-db-manager-main.cc)

add_executable (test-db-manager ${DB_M_SRC_TEST_FILES}) 
target_link_libraries(test-db-manager PUBLIC ${Boost_LIBRARIES} GTest::GTest GTest::Main)
