cmake_minimum_required(VERSION 3.16)

project(runner)

add_library(list list.h)
set_target_properties(list PROPERTIES LINKER_LANGUAGE CXX)

################ clang-format ################
list(APPEND CMAKE_MODULE_PATH $ENV{CLANG_FORMAT_SUBMODULE}/cmake)
include(ClangFormat)
target_clangformat_setup(list)