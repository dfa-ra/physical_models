//
// Created by ra on 03.12.24.
//

#ifndef UNTIL_H
#define UNTIL_H
#include <string>
#include <list>

#include "Vector.h"

//
// Created by ra on 03.12.24.
//

bool random_chance(int percent);

void clear_file(const std::string &fname);
int draw_plots(const std::list<Vector>* result, std::string name);

#endif //UNTIL_H
