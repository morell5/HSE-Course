# ставим нижнее ограничение на версию cmake для сборки проекта
cmake_minimum_required(VERSION 3.16)

# именуем проект: значение сохраняется в переменную PROJECT_NAME
project("seminar10")

# включаем файлы в поддиректория в сборку проекта
add_subdirectory(convertibility)
add_subdirectory(local_classes)
add_subdirectory(type_selection)
add_subdirectory(type_traits)