cmake_minimum_required(VERSION 3.16)

project("runner")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(allocator INTERFACE)

target_include_directories(allocator INTERFACE  ${CMAKE_CURRENT_SOURCE_DIR})