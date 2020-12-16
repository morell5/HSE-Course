# ставим нижнее ограничение на версию cmake для сборки проекта
cmake_minimum_required(VERSION 3.16)

# именуем проект: значение сохраняется в переменную PROJECT_NAME
project("seminar13")

# создаем исполняемый target
add_executable(array array.cpp)
add_executable(make_unique make_unique.cpp)
add_executable(print print.cpp)
add_executable(syntax syntax.cpp)