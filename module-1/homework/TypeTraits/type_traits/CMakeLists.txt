cmake_minimum_required(VERSION 3.16)

project("runner")

add_library(type_traits INTERFACE)

target_include_directories(type_traits INTERFACE  ${CMAKE_CURRENT_SOURCE_DIR})