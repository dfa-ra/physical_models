//
// Created by ra on 03.03.25.
//

#ifndef GEBERATION_H
#define GEBERATION_H
//
// Created by ra on 03.03.25.
//


#include <vector>

#include "Vector.h"
#include "matplot/util/common.h"

std::vector<Vector> generate_data_set_kv2(int alpha, int v_scal);
std::vector<Vector> generate_data_set_kv(int alpha, int v_scal);
std::vector<Vector> generate_data_set_def(int alpha, int v_scal);

#endif //GEBERATION_H
