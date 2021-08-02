# set the minimum required CMake version to build the project
cmake_minimum_required(VERSION 3.16)

# name the project the name is stored in PROJECT_NAME variable
project("seminar1")

# add sundirectories to the project build
add_subdirectory(float_point)
add_subdirectory(integral)
add_subdirectory(io)