cmake_minimum_required(VERSION 3.16)

project("runner")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(variant variant.cpp)