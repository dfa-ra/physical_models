//
// Created by ra on 03.03.25.
//


#include <vector>

#include "Vector.h"
#include "matplot/util/common.h"

constexpr double k = 0.05;

std::vector<Vector> generate_data_set_kv2(int alpha, int v_scal) {
    double m = 1;
    auto V = Vector(v_scal * cos(alpha * matplot::pi / 180), v_scal * sin(alpha * matplot::pi / 180), 0);
    auto pos = Vector(0.0, 0.0, 0.0);
    Vector F_c_1 = -V.normalize() * (V * V * k);
    Vector F_c_2 = -V * k;
    auto g = Vector(0, -9.81, 0);

    float t = 10;  // общее время (c)
    float dt = 0.1;  // шаг по времени (c)
    size_t steps = t / dt;

    std::vector<Vector> result;

    for (int i = 1; i < steps; i++) {
        if (pos.y < 0) break;
        result.push_back(pos);
        F_c_1 = -V.normalize() * (V * V * k);
        Vector a = g + F_c_1 / m;
        V = V + a * dt;
        pos = pos + V * dt;
    }

    return result;
    
}

std::vector<Vector> generate_data_set_kv(int alpha, int v_scal) {
    double k = 0.05;
    double m = 1;
    auto V = Vector(v_scal * cos(alpha * matplot::pi / 180), v_scal * sin(alpha * matplot::pi / 180), 0);
    auto pos = Vector(0.0, 0.0, 0.0);
    Vector F_c_1 = -V.normalize() * (V * V * k);
    Vector F_c_2 = -V * k;
    auto g = Vector(0, -9.81, 0);

    float t = 10;  // общее время (c)
    float dt = 0.1;  // шаг по времени (c)
    size_t steps = t / dt;

    std::vector<Vector> result;

    for (int i = 1; i < steps; i ++) {
        result.push_back(pos);
        if (pos.y < 0) break;
        F_c_2 = -V * k;
        Vector a = g + F_c_2 / m;
        V = V + a * dt;
        pos = pos + V * dt;
    }

    return result;
}



std::vector<Vector> generate_data_set_def(int alpha, int v_scal) {
    double k = 0.05;
    double m = 1;
    auto V = Vector(v_scal * cos(alpha * matplot::pi / 180), v_scal * sin(alpha * matplot::pi / 180), 0);
    auto pos = Vector(0.0, 0.0, 0.0);
    Vector F_c_1 = -V.normalize() * (V * V * k);
    Vector F_c_2 = -V * k;
    auto g = Vector(0, -9.81, 0);

    float t = 10;  // общее время (c)
    float dt = 0.1;  // шаг по времени (c)
    size_t steps = t / dt;

    std::vector<Vector> result;

    for (int i = 1; i < steps; i ++) {
        result.push_back(pos);
        if (pos.y < 0) break;
        Vector a = g;
        V = V + a * dt;
        pos = pos + V * dt;
    }

    return result;
}
