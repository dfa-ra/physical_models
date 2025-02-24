# Устанавливаем минимальную версию CMake
cmake_minimum_required(VERSION 3.22)

# Определяем проект как C++ проект
project(physical_models CXX)

# Устанавливаем стандарт C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF) # Отключаем вендор-специфические расширения
set(CMAKE_TOOLCHAIN_FILE "./deps/conan_toolchain.cmake" CACHE FILEPATH "")

# Добавляем исполняемый файл
add_executable(physical_models
        main.cpp
        zadacha_82/zadacha_82.cpp
        lib/includes/Vector.h
        lib/includes/until.h
        zadacha_dop/drawer/Plot.cpp
        zadacha_dop/drawer/Plot.h
        lib/src/until.cpp
        lib/src/Vector.cpp
        zadacha_dop/zadacha_dop.cpp)


# Связываем библиотеку math (`m`) с проектом
target_link_libraries(physical_models PRIVATE m)

add_subdirectory(matplotplusplus)
target_link_libraries(physical_models PUBLIC matplot)
# Если cJSON используется как C-библиотека, добавляем её как таковую
set_target_properties(physical_models PROPERTIES CXX_EXTENSIONS OFF)
set_source_files_properties(lib/cJSON/cJSON.c PROPERTIES LANGUAGE C)

# Опционально: добавляем директории заголовочных файлов
target_include_directories(physical_models PRIVATE
        lib/includes
        lib/cJSON
)