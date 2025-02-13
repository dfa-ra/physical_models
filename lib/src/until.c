
// Created by ra on 03.12.24.
//
//

#include <float.h>
#include <stdbool.h>
#include <time.h>

#include "../headers/vec.h"
#include "../headers/arr.h"


bool random_chance(int percent) {

    if (percent < 0 || percent > 100) {
        fprintf(stderr, "Процент должен быть в диапазоне от 0 до 100\n");
        return false;
    }
    int random_number = rand() % 100; // Случайное число от 0 до 99
    return random_number < percent;
}

void clear_file(const char* fname) {
    FILE* file = fopen(fname, "w"); // Открываем файл в режиме записи
    if (file == NULL) {
        perror("Ошибка при очистке файла");
        return;
    }
    fclose(file); // Закрываем файл, он теперь пуст
}

//
void save_data_to_file(char* fname, vec* result, size_t real_steps, char* name) {

    FILE* file = fopen(fname, "a");

    if (file == NULL) {
        perror("Ошибка открытия файла 0_0");
        return;
    }
    fprintf(file, "%s\n", name);
    for (size_t i = 0; i < real_steps; i++) {
        fprintf(file, "%.13Le %.13Le %.13Le\n", result[i].x, result[i].y, result[i].z);
    }

    fprintf(file, "-\n");
    fclose(file);
};

