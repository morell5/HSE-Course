# set the minimum required CMake version to build the project
cmake_minimum_required(VERSION 3.16)

# name the project the name is stored in PROJECT_NAME variable
project("seminar1")

# make executable targets
add_executable(fib fib.cpp)
add_executable(game game.cpp)
add_executable(integer integer.cpp)