
#include "Vector.h"

#include <math.h>
#include <stdio.h>

void Vector::vec_norm() {
    long double len = Vector::len();
    if (len == 0.0L) return;
    this->x = this->x / len;
    this->y = this->y / len;
    this->z = this->z / len;
}

Vector::~Vector() = default;

