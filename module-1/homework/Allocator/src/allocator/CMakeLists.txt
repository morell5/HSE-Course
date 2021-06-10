cmake_minimum_required(VERSION 3.16)

project(runner)

add_library(allocator OBJECT allocator.h)
set_target_properties(allocator PROPERTIES LINKER_LANGUAGE CXX)

################ clang-format ################
list(APPEND CMAKE_MODULE_PATH $ENV{CLANG_FORMAT_SUBMODULE}/cmake)
include(ClangFormat)
target_clangformat_setup(allocator)