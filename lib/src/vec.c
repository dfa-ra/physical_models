
#include <math.h>
#include <stdio.h>

#include "../includes/vec.h"

vec some_vec(long double x, long double y, long double z) {
    return (vec){.x = x, .y = y, .z = z};
}

vec vec_sum(const vec a, const vec b) {
    return some_vec(fma(a.x, 1.0L, b.x), fma(a.y, 1.0L, b.y), fma(a.z, 1.0L, b.z));
}

vec vec_neg(const vec a) {
    return some_vec(-a.x, -a.y, -a.z);
}

vec vec_sub(const vec a, const vec b) {
    return vec_sum(a, vec_neg(b));
}

long double vec_dot(const vec a, const vec b) {
    return fma(a.x, b.x, fma(a.y, b.y, a.z * b.z));
}

vec vec_cross(const vec a, const vec b) {
    return some_vec(fma(a.y, b.z, -a.z * b.y), fma(a.z, b.x, -a.x * b.z), fma(a.x, b.y, -a.y * b.x));
}

vec vec_mul(const vec a, const long double k) {
    return some_vec(k * a.x, k * a.y, k * a.z);
}

vec vec_div(const vec a, const long double k) {
    return some_vec(a.x / k, a.y / k, a.z / k);
}

void print_vec(const vec a) {
    printf("%.10Lg %.10Lg %.10Lg\n", a.x, a.y, a.z);
}

long double vec_len(const vec a) {
    return hypot(hypot(a.x, a.y), a.z);
}

vec vec_norm(const vec a) {
    long double len = vec_len(a);
    if (len == 0.0L) {
        return some_vec(0.0L, 0.0L, 0.0L);
    }
    return some_vec(a.x / len, a.y / len, a.z / len);
}