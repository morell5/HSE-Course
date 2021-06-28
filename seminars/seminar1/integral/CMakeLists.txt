# ставим нижнее ограничение на версию cmake для сборки проекта
cmake_minimum_required(VERSION 3.16)

# именуем проект: значение сохраняется в переменную PROJECT_NAME
project("seminar1")

# создаем исполняемые targets
add_executable(bitwise_operation bitwise_operation.cpp)
add_executable(overflow overflow.cpp)
add_executable(complement_code complement_code.cpp)