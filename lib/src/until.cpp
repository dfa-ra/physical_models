
// Created by ra on 03.12.24.
//
//


#include <list>
#include <string>
#include <iostream>
#include <fstream>
#include <string>

#include "../includes/Vector.h"



bool random_chance(int percent) {

    if (percent < 0 || percent > 100) {
        std::cerr << "Процент должен быть в диапазоне от 0 до 100\n" << std::endl;
        return false;
    }
    int random_number = rand() % 100; // Случайное число от 0 до 99
    return random_number < percent;
}

// Функция для сохранения данных в JSON-файл
int draw_plots(const std::list<Vector>* result, std::string name) {

}
