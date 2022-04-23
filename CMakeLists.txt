project(curlpp)
cmake_minimum_required(VERSION 3.22)


find_package(CURL REQUIRED)

file(GLOB_RECURSE HeaderFileList "${CMAKE_CURRENT_SOURCE_DIR}/include/*")
file(GLOB_RECURSE SourceFileList "${CMAKE_CURRENT_SOURCE_DIR}/build/src/*")
file(GLOB_RECURSE SourceFileList1 "${CMAKE_CURRENT_SOURCE_DIR}/src/curlpp/*")
option(CURLPP_BUILD_SHARED_LIBS "Build shared libraries" ON)

message(STATUS ${CMAKE_CURRENT_SOURCE_DIR})
#include_directories(PUBIC "${CMAKE_CURRENT_SOURCE_DIR}/include/")

message(STATUS ${SourceFileList1})
add_library(fucker SHARED ${HeaderFileList} ${SourceFileList})
target_include_directories(fucker PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
set_target_properties(fucker PROPERTIES OUTPUT_NAME "semi")

add_library(nigger SHARED ${HeaderFileList} ${SourceFileList1})
target_include_directories(nigger PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
set_target_properties(nigger PROPERTIES OUTPUT_NAME "main")


add_executable(main "${CMAKE_CURRENT_SOURCE_DIR}/test.cpp")
target_include_directories(main PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include"
	${CMAKE_CURRENT_SOURCE_DIR}/include/curlpp)
target_link_libraries(main PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/build/libmain.so
	/usr/lib64/libcurl.so)
