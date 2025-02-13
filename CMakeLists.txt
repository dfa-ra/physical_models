cmake_minimum_required(VERSION 3.22)
project(physical_models C)

set(CMAKE_C_STANDARD 11)

add_executable(physical_models
        main.c
        zadacha_82/zadacha_82.c
        lib/includes/vec.h
        lib/includes/until.h
        lib/includes/arr.h
        lib/src/arr.c
        lib/src/until.c
        lib/src/vec.c)

target_link_libraries(physical_models m)