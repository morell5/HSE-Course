cmake_minimum_required(VERSION 3.16)

project("runner")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(control INTERFACE)

target_include_directories(control INTERFACE  ${CMAKE_CURRENT_SOURCE_DIR})