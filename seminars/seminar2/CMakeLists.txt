# ставим нижнее ограничение на версию cmake для сборки проекта
cmake_minimum_required(VERSION 3.16)

# именуем проект: значение сохраняется в переменную PROJECT_NAME
project("seminar1")

# создаем исполняемые targets
add_executable(fib fib.cpp)
add_executable(game game.cpp)
add_executable(integer integer.cpp)