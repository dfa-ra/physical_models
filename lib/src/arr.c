//
// Created by ra on 04.11.24.
//
#include "../includes/arr.h"

array_array_double none_array_array_double = {.data = NULL, .rows = 0, .cols = 0};

array_array_double some_array_array_double(long double ** data, size_t rows, size_t cols) {
    return (array_array_double){.data = data, .rows = rows, .cols = cols};
}

array_array_double malloc_array_array_double(size_t rows, size_t cols) {
    long double** data = malloc(sizeof(long double*) * rows);

    for (size_t i = 0; i < rows; i++) {
        data[i] = malloc(sizeof(long double) * cols);
    }

    return some_array_array_double(data, rows, cols);
}

array_array_double read_array_array_double_from_file(FILE* file) {
    if (file == NULL) {
        perror("Ошибка открытия файла 0_0");
        return none_array_array_double;
    }

    size_t rows = 0;
    size_t cols = 0;
    double tmp;

    while (fscanf(file, "%lf", &tmp) != EOF) {
        if (fgetc(file) == '\n') {
            rows++;
        }
        cols++;
    }
    rows++;
    cols /= rows;

    rewind(file);
    array_array_double data = malloc_array_array_double(rows, cols);

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            fscanf(file, "%Lg", &data.data[i][j]);
            // printf("%Lg\n", data.data[i][j]);
        }
    }
    fclose(file);
    return data;
}

void print_array_array_double(array_array_double data) {
    for (size_t i = 0; i < data.rows; i++) {
        for (size_t j = 0; j < data.cols; j++) {
            printf("%.10lf - ", data.data[i][j]);
        }
        printf("\n");
    }
}

void free_array_array_double(array_array_double data) {
    for (size_t i = 0; i < data.rows; i++) {
        free(data.data[i]);
    }
    free(data.data);
}

