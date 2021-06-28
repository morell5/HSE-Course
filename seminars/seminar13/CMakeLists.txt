# ставим нижнее ограничение на версию cmake для сборки проекта
cmake_minimum_required(VERSION 3.16)

# именуем проект: значение сохраняется в переменную PROJECT_NAME
project("seminar13")

# включаем файлы в поддиректория в сборку проекта
add_subdirectory(exception)
add_subdirectory(variadic)