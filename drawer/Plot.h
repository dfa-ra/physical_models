//
// Created by ra on 19.02.25.
//

#ifndef PLOT_H
#define PLOT_H

#include <vector>
#include <string>
#include <map>
#include <matplot/matplot.h> // Используем Matplot++ вместо matplotlibcpp

#include "Vector.h"

using namespace std;

class Plot {
private:
       map<string, vector<Vector>> plots; // Хранилище для графиков
       vector<char* > colors = {  // Предопределенный список цветов
              "r", "b", "g", "m", "c", "y", "k"
          };
       size_t colorIndex = 0;

public:
       // Метод для добавления графика
       void add(const vector<Vector>& points, const string& label) {
              plots[label] = points;
       }

       void show() {
              // Очистка предыдущих графиков (если нужно)
              matplot::cla(); // Очистка текущих axes
              matplot::hold(true);
              // Добавление всех графиков
              for (const auto& plot : plots) {
                     vector<long double> x, y;

                     // Сбор данных для графика
                     for (const auto& point : plot.second) {
                            x.push_back(point.x); // Предполагаем, что Vector имеет поля x и y
                            y.push_back(point.y);
                     }
                     // Добавление графика
                     char* color = colors[colorIndex % colors.size()]; // Циклический выбор цвета
                     colorIndex += 1;

                     // Добавление графика
                     auto plt = matplot::plot(x, y, color);
                     plt->display_name(plot.first);


              }

              // Настройка графика
              matplot::title("Графики"); // Заголовок графика
              matplot::xlabel("Ось X");  // Подпись оси X
              matplot::ylabel("Ось Y");  // Подпись оси Y
              matplot::legend();            // Включаем легенду

              matplot::axis("equal");
              // Отображение всех графиков
              matplot::show();
       }

};

#endif //PLOT_H