cmake_minimum_required(VERSION 3.16)

project("list")

add_executable(list tests.cpp list.h list.cpp)

target_compile_options(list PUBLIC -fsanitize=address,undefined,leak)
 target_link_options(list PUBLIC -fsanitize=address,undefined,leak)

