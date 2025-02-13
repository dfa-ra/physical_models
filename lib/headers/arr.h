//
// Created by ra on 04.11.24.
//

#ifndef ARR_H
#define ARR_H
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long double** data;
    size_t cols;
    size_t rows;
} array_array_double;

extern array_array_double none_array_array_double;

array_array_double some_array_array_double(long double ** data, size_t rows, size_t cols);
array_array_double malloc_array_array_double(size_t rows, size_t cols);
array_array_double read_array_array_double_from_file(FILE* file);
void print_array_array_double(array_array_double data);
void free_array_array_double(array_array_double data);

#endif //ARR_H
