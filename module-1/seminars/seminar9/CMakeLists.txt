# ставим нижнее ограничение на версию cmake для сборки проекта
cmake_minimum_required(VERSION 3.16)

# именуем проект: значение сохраняется в переменную PROJECT_NAME
project("seminar9")

# включаем файлы в поддиректория в сборку проекта
add_subdirectory(index_of)
add_subdirectory(int2type)
add_subdirectory(static_assert)
add_subdirectory(type2type)