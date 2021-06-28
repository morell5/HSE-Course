cmake_minimum_required(VERSION 3.16)

include(GoogleTest)

project("runner")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

################  clang-tidy  ################
set(CMAKE_CXX_CLANG_TIDY "clang-tidy;--fix-errors;-header-filter=.")

add_executable(runner 0_consexpr_function.cpp)

################ clang-format ################
list(APPEND CMAKE_MODULE_PATH $ENV{CLANG_FORMAT_SUBMODULE}/cmake)
include(ClangFormat)
target_clangformat_setup(runner)