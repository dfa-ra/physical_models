//
// Created by ra on 31.03.25.
//

#include <cmath>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <iostream>

bool in_serpinskiy_kvadrat(float x, float y, float size, int depth) {
    if (depth == 0) return true;

    float new_size = size / 3;

    if (new_size <= x && x < 2 * new_size && new_size <= y && y < 2 * new_size)
        return false;

    return in_serpinskiy_kvadrat( std::fmod(x, new_size), std::fmod(y, new_size), new_size, depth - 1);
}

float calculate_square_serpinskiy_kvadrat(int depth) {
    std::srand(std::time(0));
    int in_count = 0;
    int M = 100000;
    float start = 0, width = 4;

    for (int i = 0; i < M; i++) {
        float random_x = start + static_cast <float> (std::rand()) / static_cast <float> (RAND_MAX) * width;
        float random_y = start + static_cast <float> (std::rand()) / static_cast <float> (RAND_MAX) * width;

        if (in_serpinskiy_kvadrat(random_x, random_y, width, depth)) {
            in_count++;
        }
    }
    return width * width * (static_cast<float>(in_count) / static_cast<float>(M));
}


void zadacha_serpinskiy_kvadrat(){

    std::vector values = {3, 10, 30, 50, 70, 100};

    for (int val: values) {
        std::cout << "Задание \"квадрат Серпинского\" для глубины " << val << " : " << calculate_square_serpinskiy_kvadrat(val) << std:: endl;
    }

}