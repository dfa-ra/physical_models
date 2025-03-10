//
// Created by ra on 13.02.25.
//

#include <stdio.h>
#include <vector>

#include "../lib/includes/Vector.h"
#include "../lib/includes/until.h"
#include "../drawer/Plot.h"

// функция перевода скрости  гр/мин -> гр/мс
float v(const float v) {
    return v / 60 / 1;
}

void zadacha_82() {
    Plot plot;

    printf("============ ZADACHA 82 ============\n");

    // Начальная температура в градусах
    float a = 10;
    // Конечная температура печи в градусах
    float b = 100;
    // Скорость нагревания печи (градус/мин)
    float v_pechi = (b - a) / 60;
    float T_metalla = a;
    float T_pechi = a;
    float dT = T_pechi - T_metalla;

    // Разность температуры металла и печи при которой скорость нагрева dt
    float T = 20;
    // Скорость нагревания металла (градусов/мин)
    float kT = 1;
    // Длительность эксперимента в mc
    float t = 60 * 60;  // общее время (c)
    float dt = 1;  // шаг по времени (c)
    size_t steps = t / dt;

    std::vector<Vector> result_t_pechi;
    std::vector<Vector> result_t_metalla;

    for (int i = 1; i < steps; i ++) {
        // Нагреваем печь
        T_pechi += v(v_pechi);
        auto vec = Vector(v(static_cast<float>(i)) ,T_pechi, 0);
        result_t_pechi.push_back(vec);
        // Находим разницу
        dT = T_pechi - T_metalla;

        // Увеличиваем температуру металла
        T_metalla += dT * v(kT) / T;
        vec = Vector(v(static_cast<float>(i)), T_metalla, 0);
        result_t_metalla.push_back(vec);
    }

    printf("конечна темепература печи %f\n", T_pechi);
    printf("конечна темепература металла %f\n", T_metalla);

    plot.add(result_t_metalla, "график 1");
    plot.add(result_t_pechi, "график 2");

    plot.show();
    printf("====================================\n");
}