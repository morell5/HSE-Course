# ставим нижнее ограничение на версию cmake для сборки проекта
cmake_minimum_required(VERSION 3.16)

# именуем проект: значение сохраняется в переменную PROJECT_NAME
project("lecture15")

# создаем исполняемый target
add_executable(unique_ptr unique_ptr.cpp)