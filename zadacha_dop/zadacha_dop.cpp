//
// Created by ra on 18.02.25.
//

#include <list>
#include <vector>

#include "generation.h"
#include "../lib/includes/Vector.h"
#include "../drawer/Plot.h"

using namespace std;

void zadacha_dop() {
    Plot plot;

    int alpha = 45;
    int V_scal = 30;
    Vector max = Vector();
    vector<Vector> max_result;
    int max_alpha = 0;

    plot.add(generate_data_set_kv2(alpha, V_scal), "график F_{сoпр} = k*v^2");
    plot.add(generate_data_set_kv(alpha, V_scal), "график F_{сoпр} = k*v");
    plot.add(generate_data_set_def(alpha, V_scal), "график F_{сoпр} = 0");

    // for (int i = 5; i < 85; i++) {
    //     vector<Vector> result = generate_data_set_kv2(i, V_scal);
    //     if (result.at(result.size()-1).x > max.x) {
    //         max = result.at(result.size()-1);
    //         max_alpha = i;
    //         max_result = result;
    //     }
    // }
    //
    // cout << max.x << " " << max_alpha << endl;
    // plot.add(max_result, "график F_{сoпр} = k*v^2");
    // max_alpha = 0;
    // max = Vector();
    //
    // for (int i = 5; i < 85; i++) {
    //     vector<Vector> result = generate_data_set_kv(i, V_scal);
    //     if (result.at(result.size()-1).x > max.x) {
    //         max = result.at(result.size()-1);
    //         max_alpha = i;
    //         max_result = result;
    //     }
    // }
    // cout << max.x << " " << max_alpha << endl;
    // plot.add(max_result, "график F_{сoпр} = k*v");

    // Отрисовываем графики
    plot.show();
}
