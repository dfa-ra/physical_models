//
// Created by ra on 18.02.25.
//

#include <list>
#include <vector>

#include "../lib/includes/Vector.h"
#include "drawer/Plot.h"

using namespace std;

void zadacha_dop() {
    Plot plot;

    int alpha = 20;
    int V_scal = 30;
    double k = 0.05;
    double m = 1;
    auto V = Vector(V_scal * cos(alpha * matplot::pi / 180), V_scal * sin(alpha * matplot::pi / 180), 0);
    auto pos = Vector(0.0, 0.0, 0.0);
    Vector F_c_1 = -V.normalize() * (V * V * k);
    Vector F_c_2 = -V * k;
    auto g = Vector(0, -9.81, 0);

    float t = 10;  // общее время (c)
    float dt = 0.1;  // шаг по времени (c)
    size_t steps = t / dt;

    vector<Vector> result_1;
    vector<Vector> result_2;
    vector<Vector> default_1;

    for (int i = 1; i < steps; i ++) {
        result_1.push_back(pos);
        if (pos.y < 0) break;
        F_c_1 = -V.normalize() * (V * V * k);
        Vector a = g + F_c_1 / m;
        V = V + a * dt;
        pos = pos + V * dt;
    }
    plot.add(result_1, "график F_{сoпр} = k*v^2");

    V = Vector(V_scal * cos(alpha * matplot::pi / 180), V_scal * sin(alpha * matplot::pi / 180), 0);
    pos = Vector(0.0, 0.0, 0.0);

    for (int i = 1; i < steps; i ++) {
        result_2.push_back(pos);
        if (pos.y < 0) break;
        F_c_2 = -V * k;
        Vector a = g + F_c_2 / m;
        V = V + a * dt;
        pos = pos + V * dt;
    }
    plot.add(result_2, "график F_{сoпр} = k*v");

    V = Vector(V_scal * cos(alpha * matplot::pi / 180), V_scal * sin(alpha * matplot::pi / 180), 0);
    pos = Vector(0.0, 0.0, 0.0);

    for (int i = 1; i < steps; i ++) {
        default_1.push_back(pos);
        if (pos.y < 0) break;
        Vector a = g;
        V = V + a * dt;
        pos = pos + V * dt;
    }
    plot.add(default_1, "график F_{сoпр} = 0");

    // Отрисовываем графики
    plot.show();
}
