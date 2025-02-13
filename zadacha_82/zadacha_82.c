//
// Created by ra on 13.02.25.
//

#include <stdio.h>
#include "../lib/headers/vec.h"
#include "../lib/headers/until.h"

// функция перевода скрости  гр/мин -> гр/мс
float v(const float v) {
    return v / 60 / 1;
}

void zadacha_82() {

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
    float T = 90;
    // Скорость нагревания металла (градусов/мин)
    float kT = 1;
    // Длительность эксперимента в mc
    float t = 60 * 60;  // общее время (c)
    float dt = 1;  // шаг по времени (c)
    size_t steps = t / dt;

    vec result_t_pechi[steps];
    vec result_t_metalla[steps];

    for (int i = 1; i < steps; i ++) {
        // Нагреваем печь
        T_pechi += v(v_pechi);
        result_t_pechi[i-1] = (vec){ v(i) ,T_pechi, 0};
        // Находим разницу
        dT = T_pechi - T_metalla;

        // Увеличиваем температуру металла
        T_metalla += dT * v(kT) / T;
        result_t_metalla[i-1] = (vec){v(i), T_metalla, 0};
    }

    printf("конечна темепература печи %f\n", T_pechi);
    printf("конечна темепература металла %f\n", T_metalla);
    clear_file("/media/ra/_work/ra/ITMO/PHISICS/physical_models/drawer/data.txt");
    save_data_to_file("/media/ra/_work/ra/ITMO/PHISICS/physical_models/drawer/data.txt", result_t_pechi, steps - 1, "температура печи");
    save_data_to_file("/media/ra/_work/ra/ITMO/PHISICS/physical_models/drawer/data.txt", result_t_metalla, steps - 1, "температура металла");
    printf("====================================\n");
}
