cmake_minimum_required(VERSION 3.16)

project("runner")

add_library(typelist INTERFACE)

target_include_directories(typelist INTERFACE  ${CMAKE_CURRENT_SOURCE_DIR})