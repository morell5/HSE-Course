# set the minimum required CMake version to build the project
cmake_minimum_required(VERSION 3.16)

# name the project the name is stored in PROJECT_NAME variable
project("seminar1")

# make executable targets
add_executable(bitwise_operation bitwise_operation.cpp)
add_executable(overflow overflow.cpp)
add_executable(complement_code complement_code.cpp)