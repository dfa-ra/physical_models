#include <chrono>
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <thread>
#include <3rd_party/cimg/CImg.h>

#include "Vector.h"
#include "matplot/freestanding/axes_functions.h"
#include "matplot/util/concepts.h"
long double k = 1500.0 / (2 * 4.7e12);

class Planet {
public:
    double w = 1500;
    double h = 1500;

    int index;
    Vector coords;
    long double r;
    Vector V;
    Vector a;
    double m;

    Planet(const int index, const Vector &coords, const long double r, const Vector &V, const Vector &a, const double m) {
        this->index = index;
        this->coords = coords + Vector{w / 2, h / 2, 0} / k;
        this->r = r;
        this->V = V;
        this->a = a;
        this->m = m;
    }

    [[nodiscard]] Vector calc_p() const {
        return V * m;
    }
};


class Scene2 {
private:
    sf::RenderWindow window;
    std::vector<sf::CircleShape> circles;
    double koef = 5;


public:

    Scene2(int width = 1500, int height = 1500, const std::string& title = "Scene")
        : window(sf::VideoMode(width, height), title)
    {
        initializeScene();
    }

    void initializeScene() {
    }

    void addCircle(double x, double y, double radius, const sf::Color& color = sf::Color::Red) {
        radius *= 10;
        if (radius < 1.0) {
            radius = 0.4 + radius * (1 - 0.4);
        }
        sf::CircleShape circle(radius * koef);
        circle.setPosition(x - radius * koef, y - radius * koef);
        circle.setFillColor(color);
        circles.push_back(circle);
    }

    void moveCircle(int index, double dx, double dy) {
        if (index >= 0 && index < circles.size()) {
            circles[index].move(dx, dy);
        }
    }

    void setCirclePosition(const int index, const Planet& circle) {
        if (index < 0 || index >= circles.size()) return;
        double radius = circle.r;
        if (radius < 1.0) {
            radius = 0.1 + radius * (1 - 0.1);
        }
        circles[index].setPosition(circle.coords.x - radius * koef, circle.coords.y - radius * koef);
    }


    bool update() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return false;
            }
        }

        window.clear(sf::Color::White);
        for (const auto& circle : circles) {
            window.draw(circle);
        }

        window.display();

        return true;
    }

    bool isOpen() const { return window.isOpen(); }
};

Vector calculateAcceleration(const Planet& planet, const Planet& otherPlanet, float G) {
    Vector distance = planet.coords - otherPlanet.coords;
    long double dist = distance.magnitude();
    return distance * (-G * otherPlanet.m / pow(dist, 3));
}

void updatePlanet(Planet &planet, const Planet &otherPlanet, float deltaTime, float G) {
    Vector a1 = calculateAcceleration(planet, otherPlanet, G);
    Vector v1 = planet.V + a1 * 0.5 * deltaTime;

    Vector a2 = calculateAcceleration(planet, otherPlanet, G);
    Vector v2 = planet.V + a2 * 0.5 * deltaTime;

    Vector a3 = calculateAcceleration(planet, otherPlanet, G);
    Vector v3 = planet.V + a3 * deltaTime;

    Vector a4 = calculateAcceleration(planet, otherPlanet, G);

    Vector a_avg = (a1 + a2 * 2 + a3 * 2 + a4) / 6.0;

    planet.a = planet.a + a_avg;
}


void zadacha_solnechn_system() {
    std::srand(std::time(nullptr));

    std::pair<std::pair<double, double>, std::pair<double, double>> coords;

    std::vector<Planet> tela;



    Planet sun = {0, Vector{0, 0, 0}, 696000000, Vector{0, 0, 0}, Vector{0, 0, 0}, 1.988*1e30};

    Planet mercury = {1, Vector{5.79e10, 0, 0}, 2439700, Vector{0, 47870, 0}, Vector{0, 0, 0}, 3.30e23};

    Planet venus = {2, Vector{1.082e11, 0, 0}, 6051800, Vector{0, 35020, 0}, Vector{0, 0, 0}, 4.87e24};

    Planet earth = {3, Vector{1.496e11, 0, 0}, 6371000, Vector{0, 29780, 0}, Vector{0, 0, 0}, 5.97e24};

    Planet mars = {4, Vector{2.279e11, 0, 0}, 3389500, Vector{0, 24130, 0}, Vector{0, 0, 0}, 6.42e23};

    Planet jupiter = {5, Vector{7.785e11, 0, 0}, 69911000, Vector{0, 13070, 0}, Vector{0, 0, 0}, 1.90e27};

    Planet saturn = {6, Vector{1.433e12, 0, 0}, 58232000, Vector{0, 9680, 0}, Vector{0, 0, 0}, 5.68e26};

    Planet uranus = {7, Vector{2.877e12, 0, 0}, 25362000, Vector{0, 6800, 0}, Vector{0, 0, 0}, 8.68e25};

    Planet neptune = {8, Vector{4.503e12, 0, 0}, 24622000, Vector{0, 5430, 0}, Vector{0, 0, 0}, 1.02e26};



    Scene2 scene;
    std::cout << sun.coords << sun.r << std::endl;
    std::cout << earth.coords << earth.r << std::endl;
    scene.addCircle(sun.coords.x * k, sun.coords.y * k,sun.r * k, sf::Color::Yellow);
    scene.addCircle(mercury.coords.x * k, mercury.coords.y * k,mercury.r * k, sf::Color::Green);
    scene.addCircle(venus.coords.x * k, venus.coords.y * k,venus.r * k, sf::Color::Green);
    scene.addCircle(earth.coords.x * k, earth.coords.y * k,earth.r * k, sf::Color::Green);
    scene.addCircle(mars.coords.x * k, mars.coords.y * k,mars.r * k, sf::Color::Green);
    scene.addCircle(jupiter.coords.x * k, jupiter.coords.y * k,jupiter.r * k, sf::Color::Green);
    scene.addCircle(saturn.coords.x * k, saturn.coords.y * k,saturn.r * k, sf::Color::Green);
    scene.addCircle(uranus.coords.x * k, uranus.coords.y * k,uranus.r * k, sf::Color::Green);

    tela.push_back(sun);
    tela.push_back(mercury);
    tela.push_back(venus);
    tela.push_back(earth);
    tela.push_back(mars);
    tela.push_back(jupiter);
    tela.push_back(saturn);
    tela.push_back(uranus);

    float deltaTime = 3600 * 12;
    // float G = 6.67430 * pow(10, -11) * k * k * k;
    float G = 6.67430 * pow(10, -11);
    while (scene.isOpen()) {

        for (int i = 0; i < tela.size(); i++) {
            Planet *circle = &tela[i];
            circle->a = Vector{0, 0, 0};
            for (int j = 0; j < tela.size(); j++) {
                if (i == j) continue;

                updatePlanet(tela[i], tela[j], deltaTime, G);

                //
                // Vector distance = circle->coords - tela[j].coords;
                // const long double dist = distance.magnitude();
                // circle->a = circle->a + distance * (-G * tela[j].m / pow(dist, 3));
                // circle->V = circle->V + circle->a * deltaTime;
                // circle->coords = circle->coords + circle->V * deltaTime;
            }
            circle->V = circle->V + circle->a * deltaTime;
            circle->coords = circle->coords + circle->V * deltaTime;

            Planet pl = tela[i];
            // std::cout << "-----------" << std::endl;
            // std::cout << pl.coords << std::endl;
            pl.coords = pl.coords * k;
            pl.r = pl.r * k;

            // std::cout << pl.r << std::endl;
            // std::cout << pl.index << std::endl;
            // std::cout << pl.coords << std::endl;
            // std::cout << "============" << std::endl;
            scene.setCirclePosition(pl.index, pl);
        }
        // std::cout << "next frame" << std::endl;
        if (!scene.update()) break;

        sf::sleep(sf::milliseconds(16)); // ~60 FPS
    }
}
