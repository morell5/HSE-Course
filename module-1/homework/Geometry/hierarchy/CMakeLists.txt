cmake_minimum_required(VERSION 3.16)

AUX_SOURCE_DIRECTORY(. src) 
add_library(hierarchy ${src} constants.h operations.h operations.cpp)

target_include_directories(hierarchy PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})