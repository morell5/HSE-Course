# ставим нижнее ограничение на версию cmake для сборки проекта
cmake_minimum_required(VERSION 3.16)

# именуем проект: значение сохраняется в переменную PROJECT_NAME
project("seminar13")

# создаем исполняемый target
add_executable(function_try_block function_try_block.cpp)