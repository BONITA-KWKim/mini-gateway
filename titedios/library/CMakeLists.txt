cmake_minimum_required (VERSION 3.5.1)
message ("libraries")

if (NOT MSVC)
  add_definitions (-std=c++11)
else ()
  add_definitions (-D_WIN32_WINNT=0x600)
endif()

# default deriectory
set (LIB_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src)
set (LIB_FILES ${LIB_SRC}/util-mmf.cc ${LIB_SRC}/parser.cc ${LIB_SRC}/base64.cc)

# header files
include_directories (${CMAKE_CURRENT_SOURCE_DIR}/../include)

# create .a file
add_library (minigwutils STATIC ${LIB_FILES}) 

# installation
install (TARGETS minigwutils
         ARCHIVE DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/..)
