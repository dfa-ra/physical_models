#include <cmath>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <iostream>


std::pair<float, float> search_max_min_f(float start, float width, const std::function<float(float, float, float)>& f, int args) {
    float max_f = -std::numeric_limits<float>::infinity();
    float min_f = std::numeric_limits<float>::infinity();
    const float step = 0.01f;

    if (args == 3) {
        for (float x = start; x <= start + width; x += step) {
            for (float y = start; y <= start + width; y += step) {
                for (float z = start; z <= start + width; z += step) {
                    float current = f(x, y, z);
                    if (current > max_f) {
                        max_f = current;
                    }
                    if (current < min_f) {
                        min_f = current;
                    }
                }
            }
        }
    }
    else if (args == 2) {
        for (float x = start; x <= start + width; x += step) {
            for (float y = start; y <= start + width; y += step) {
                float current = f(x, y, 0.0f);
                if (current > max_f) {
                    max_f = current;
                }
                if (current < min_f) {
                    min_f = current;
                }
            }
        }
    }
    else if (args == 1) {
        for (float x = start; x <= start + width; x += step) {
            float current = f(x, 0.0f, 0.0f);
            if (current > max_f) {
                max_f = current;
            }
            if (current < min_f) {
                min_f = current;
            }
        }
    }

    return {max_f, min_f};
}

float calculate(float start, float width, int M, const std::function<float(float, float, float)>& f, int args) {
    std::srand(std::time(0));

    float V = std::pow(width, args);
    int count_in = 0;
    std::pair<float, float> extremum_f = search_max_min_f(start, width, f, args);

    V *= extremum_f.first;

    for (int i = 0; i < M; i++) {
        float random_x = start + static_cast <float> (std::rand()) / static_cast <float> (RAND_MAX) * width;
        float random_y = start + static_cast <float> (std::rand()) / static_cast <float> (RAND_MAX) * width;
        float random_z = start + static_cast <float> (std::rand()) / static_cast <float> (RAND_MAX) * width;
        float random_k = extremum_f.second + static_cast <float> (std::rand()) / static_cast <float> (RAND_MAX) * (std::abs(extremum_f.first) + std::abs(extremum_f.second));

        if (random_k >= 0) {
            if (f(random_x, random_y, random_z) >= random_k)
                count_in++;
        }
        else {
            if (f(random_x, random_y, random_z) <= random_k)
                count_in--;
        }
    }

    return V * (static_cast<float>(count_in) / static_cast<float>(M));
}

void zadacha_montecarlo() {

    auto f1 = [](const float x, const float y, const float z) {
        return (x + y) * (x + y) * (z + 1);
    };

    auto f2 = [](const float x, const float y, const float z) {
        return std::exp(-x) * std::sqrt(std::abs(x));
    };


    std::cout << "Задание 1: " << calculate(-1, 2, 100000, f1, 3) << std::endl;
    std::cout << "Задание 2: " << calculate(-1, 2, 100000, f2, 1) << std::endl;

}
