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
        drawer/Plot.cpp
        drawer/Plot.h
        lib/src/until.cpp
        lib/src/Vector.cpp
        zadacha_dop/zadacha_dop.cpp
        zadacha_dop/generation.cpp
        zadacha_dop/generation.h
        zadacha_wave/zadacha_wave.cpp
        zadacha_montecarlo/zadacha_montecarlo.cpp
        zadacha_serpinskiy_kvadrat/zadacha_serpinskiy_kvadrat.cpp
        zadacha_chёt_impulse/zadacha_chёt_impulse.cpp
        zadacha_solnechn_system/zadacha_solnechn_system.cpp)

# Подключение SFML
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
target_link_libraries(physical_models PUBLIC sfml-graphics sfml-audio)

# Подключение ALSA (libasound)
find_package(PkgConfig REQUIRED)
pkg_check_modules(ALSA REQUIRED alsa)
target_include_directories(physical_models PRIVATE ${ALSA_INCLUDE_DIRS})
target_link_libraries(physical_models PUBLIC ${ALSA_LIBRARIES})

# Связываем библиотеку math (`m`) с проектом
target_link_libraries(physical_models PRIVATE m)

# Подключение matplot++
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
