//
// Created by ra on 03.12.24.
//

#ifndef UNTIL_H
#define UNTIL_H
#include <stdbool.h>

#include "vec.h"

//
// Created by ra on 03.12.24.
//

bool random_chance(int percent);

void clear_file(const char* fname);
void save_data_to_file(char* fname, vec* result, size_t real_steps, char* name);

#endif //UNTIL_H
