//
// Created by ra on 04.11.24.
//

#ifndef VEC_H
#define VEC_H


typedef struct {
    long double x;
    long double y;
    long double z;
} vec;


vec some_vec(long double x, long double y, long double z);
vec vec_sum(vec a, vec b);
vec vec_neg(vec a);
vec vec_sub(vec a, vec b);
long double vec_dot(vec a, vec b);
vec vec_cross(vec a, vec b);
vec vec_mul(vec a, long double k);
vec vec_div(vec a, long double k);
void print_vec(vec a);

#endif //VEC_H
