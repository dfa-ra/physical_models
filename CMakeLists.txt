cmake_minimum_required(VERSION 3.22)
project(physical_models C)

set(CMAKE_C_STANDARD 11)

add_executable(physical_models
        main.c
        zadacha_82/zadacha_82.c
        lib/headers/vec.h
        lib/headers/until.h
        lib/headers/arr.h
        lib/src/arr.c
        lib/src/until.c
        lib/src/vec.c)

target_link_libraries(physical_models m)