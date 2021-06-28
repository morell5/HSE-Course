cmake_minimum_required(VERSION 3.16)

project(runner)

add_library(type_traits OBJECT is_copy_constructible.h is_nothrow_move_constructible.h move_if_noexcept.h utility.h)
set_target_properties(type_traits PROPERTIES LINKER_LANGUAGE CXX)

################ clang-format ################
list(APPEND CMAKE_MODULE_PATH $ENV{CLANG_FORMAT_SUBMODULE}/cmake)
include(ClangFormat)
target_clangformat_setup(type_traits)