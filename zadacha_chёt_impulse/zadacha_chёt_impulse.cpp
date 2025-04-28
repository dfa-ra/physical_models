#include <chrono>
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <thread>
#include <3rd_party/cimg/CImg.h>

#include "Vector.h"
#include "matplot/freestanding/axes_functions.h"
#include "matplot/util/concepts.h"

class Circles {
public:
    int index;
    Vector coords;
    double r;
    Vector V;
    Vector a;
    double m;

    Circles(const int index, const Vector coords, const double r, const Vector &V, const Vector &a, const double m) {
        this->index = index;
        this->coords = coords;
        this->r = r;
        this->V = V;
        this->a = a;
        this->m = m;
    }

    [[nodiscard]] Vector calc_p() const {
        return V * m;
    }
};


class Scene {
private:
    sf::RenderWindow window;
    std::vector<sf::CircleShape> circles;
    std::vector<sf::ConvexShape> boxs;
    double M = 1000000000;

    static bool checkBlockCollision(const sf::CircleShape& circle, const sf::ConvexShape& block) {
        sf::Vector2f center = circle.getPosition() + sf::Vector2f(circle.getRadius(), circle.getRadius());
        float radius = circle.getRadius();

        for (size_t i = 0; i < block.getPointCount(); ++i) {
            sf::Vector2f p1 = block.getPoint(i);
            sf::Vector2f p2 = block.getPoint((i + 1) % block.getPointCount());

            p1 = block.getTransform().transformPoint(p1);
            p2 = block.getTransform().transformPoint(p2);

            if (checkLineCircleCollision(p1, p2, center, radius)) {
                return true;
            }
        }

        return isPointInsideBlock(center, block);
    }

    static bool checkLineCircleCollision(const sf::Vector2f& p1, const sf::Vector2f& p2,
                                         const sf::Vector2f& center, float radius) {
        sf::Vector2f lineDir = p2 - p1;
        sf::Vector2f toCenter = center - p1;
        float lineLengthSq = lineDir.x * lineDir.x + lineDir.y * lineDir.y;
        float projection = (toCenter.x * lineDir.x + toCenter.y * lineDir.y) / lineLengthSq;

        projection = std::max(0.f, std::min(1.f, projection));

        sf::Vector2f closestPoint = p1 + projection * lineDir;
        float distanceSq = (center.x - closestPoint.x) * (center.x - closestPoint.x) +
                          (center.y - closestPoint.y) * (center.y - closestPoint.y);

        return distanceSq <= (radius * radius);
    }

    static bool isPointInsideBlock(const sf::Vector2f& point, const sf::ConvexShape& block) {
        int intersections = 0;
        size_t count = block.getPointCount();

        for (size_t i = 0; i < count; ++i) {
            sf::Vector2f p1 = block.getPoint(i);
            sf::Vector2f p2 = block.getPoint((i + 1) % count);

            // Переводим в глобальные координаты
            p1 = block.getTransform().transformPoint(p1);
            p2 = block.getTransform().transformPoint(p2);

            if ((p1.y > point.y) != (p2.y > point.y)) {
                float x_intersect = (p2.x - p1.x) * (point.y - p1.y) / (p2.y - p1.y) + p1.x;
                if (point.x <= x_intersect) {
                    intersections++;
                }
            }
        }
        return (intersections % 2) == 1;
    }

public:
    Scene(int width = 1500, int height = 1500, const std::string& title = "Scene")
        : window(sf::VideoMode(width, height), title)
    {
        initializeScene();
    }

    void initializeScene() {
        createFunnel();
    }

    void createFunnel() {

        sf::ConvexShape block1;
        sf::ConvexShape block2;
        sf::ConvexShape tr;

        block1.setPointCount(4);
        block1.setPoint(0, sf::Vector2f(0, 50));
        block1.setPoint(1, sf::Vector2f(0, 30));
        block1.setPoint(2, sf::Vector2f(650, 380));
        block1.setPoint(3, sf::Vector2f(650, 400));
        block1.setFillColor(sf::Color(180, 180, 180, 150)); // Полупрозрачный
        block1.setOutlineThickness(2.f);
        block1.setOutlineColor(sf::Color::Black);

        block2.setPointCount(4);
        block2.setPoint(0, sf::Vector2f(1500, 50));
        block2.setPoint(1, sf::Vector2f(1500, 30));
        block2.setPoint(2, sf::Vector2f(850, 380));
        block2.setPoint(3, sf::Vector2f(850, 400));
        block2.setFillColor(sf::Color(180, 180, 180, 150));
        block2.setOutlineThickness(2.f);
        block2.setOutlineColor(sf::Color::Black);
        //
        // tr.setPointCount(6);
        // tr.setPoint(0, sf::Vector2f(700, 550));
        // tr.setPoint(1, sf::Vector2f(550, 700));
        // tr.setPoint(2, sf::Vector2f(550, 720));
        // tr.setPoint(3, sf::Vector2f(700, 570));
        // tr.setPoint(4, sf::Vector2f(850, 720));
        // tr.setPoint(5, sf::Vector2f(850, 700));
        // tr.setFillColor(sf::Color(180, 180, 180, 150));
        // tr.setOutlineThickness(2.f);
        // tr.setOutlineColor(sf::Color::Black);

        boxs.push_back(block1);
        boxs.push_back(block2);
        // boxs.push_back(tr);
        for (int i = 0; i < 31; i++) {
            sf::ConvexShape box;
            box.setPointCount(4);
            box.setPoint(0, sf::Vector2f(10.0 + i * 49 - 3, 1300));
            box.setPoint(1, sf::Vector2f(10.0 + i * 49 + 3, 1300));
            box.setPoint(2, sf::Vector2f(10.0 + i * 49 + 3, 1500));
            box.setPoint(3, sf::Vector2f(10.0 + i * 49 - 3, 1500));
            box.setFillColor(sf::Color(180, 180, 180, 150));
            box.setOutlineThickness(2.f);
            box.setOutlineColor(sf::Color::Black);
            boxs.push_back(box);
        }

    }

    void addCircle(double x, double y, double radius, const sf::Color& color = sf::Color::Red) {
        sf::CircleShape circle(radius);
        circle.setPosition(x - radius, y - radius);
        circle.setFillColor(color);
        circles.push_back(circle);
    }

    void moveCircle(int index, double dx, double dy) {
        if (index >= 0 && index < circles.size()) {
            circles[index].move(dx, dy);
        }
    }

    void setCirclePosition(int index, Circles& circle) {
    if (index < 0 || index >= circles.size()) return;

    // Обновляем позицию
    circles[index].setPosition(circle.coords.x - circle.r, circle.coords.y - circle.r);

    // Проверка границ экрана (как было раньше)
    if (circle.coords.x - circle.r < 0) {
        circle.coords.x = circle.r;
        circle.V.x = -circle.V.x * 0.8;
    }
    if (circle.coords.x + circle.r > window.getSize().x) {
        circle.coords.x = window.getSize().x - circle.r;
        circle.V.x = -circle.V.x * 0.8;
    }
    if (circle.coords.y - circle.r < 0) {
        circle.coords.y = circle.r;
        circle.V.y = -circle.V.y * 0.8;
    }
    if (circle.coords.y + circle.r > window.getSize().y) {
        circle.coords.y = window.getSize().y - circle.r;
        circle.V.y = -circle.V.y * 0.8;
    }


    for (const auto& block : boxs) {
        if (checkBlockCollision(circles[index], block)) {
            sf::Vector2f normal = findCollisionNormal(circles[index], block);

            float velocityAlongNormal = circle.V.x * normal.x + circle.V.y * normal.y;

            circle.V.x -= (1.0f + 0.9f) * velocityAlongNormal * normal.x;
            circle.V.y -= (1.0f + 0.9f) * velocityAlongNormal * normal.y;
        }
    }
}


sf::Vector2f findCollisionNormal(const sf::CircleShape& circle, const sf::ConvexShape& block) {
    sf::Vector2f center = circle.getPosition() + sf::Vector2f(circle.getRadius(), circle.getRadius());
    float minDistance = std::numeric_limits<float>::max();
    sf::Vector2f normal;

    for (size_t i = 0; i < block.getPointCount(); ++i) {
        sf::Vector2f p1 = block.getTransform().transformPoint(block.getPoint(i));
        sf::Vector2f p2 = block.getTransform().transformPoint(block.getPoint((i + 1) % block.getPointCount()));


        sf::Vector2f edge = p2 - p1;
        sf::Vector2f edgeNormal = sf::Vector2f(-edge.y, edge.x);
        float length = std::sqrt(edgeNormal.x * edgeNormal.x + edgeNormal.y * edgeNormal.y);
        edgeNormal /= length;

        float distance = std::abs((center.x - p1.x) * edgeNormal.x + (center.y - p1.y) * edgeNormal.y);

        if (distance < minDistance) {
            minDistance = distance;
            normal = edgeNormal;
        }
    }

    return normal;
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

        for (const auto& box : boxs) {
            window.draw(box);
        }
        window.display();

        return true;
    }

    bool isOpen() const { return window.isOpen(); }
};


bool are_balls_approaching(const Circles& a, const Circles& b) {
    // Вектор от a к b
    Vector ab_dir = b.coords - a.coords;
    Vector ba_dir = a.coords - b.coords;

    // Нормализуем векторы (делаем длиной 1)
    ab_dir = ab_dir.normalize();
    ba_dir = ba_dir.normalize();

    // Проекции скоростей на линию между центрами
    double a_proj = a.V.dot(ab_dir);
    double b_proj = b.V.dot(ba_dir);

    // Если проекции положительные - шары сближаются
    return (a_proj > 0) && (b_proj > 0);
}

void zadacha_chёt_impulse() {
    std::srand(std::time(nullptr));

    std::pair<std::pair<double, double>, std::pair<double, double>> coords;

    std::vector<Circles> circles;
    std::vector<Circles> static_circles;

    for (int i = 0; i < 31; i++) {
        for (int j = 0; j < 19; j++) {
            Circles circle(i, Vector{10.0 + i * 49 , 400.0 + j * 49, 0}, 10, Vector{0, 0.0, 0.0}, Vector{0, 0, 0}, 1000000000);
            static_circles.push_back(circle);
        }
    }

    double radius = 10, delta = 1;
    int M_max = 20, m_min = 19;
    int rows = 7;
    double k = (1500 - 200) / (radius * 2 + delta) ;
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < rows; j++) {
            double m = std::rand() % (M_max - m_min) + m_min;
            Circles circle1(rows * i + j, Vector{100.0 + 1300 * 1 / k * i , j * 2 * (radius + 1) , 0.0}, radius * m / M_max, Vector{0, 0.0, 0.0}, Vector{0, 0.50, 0.0}, m);
            circles.push_back(circle1);
        }
    }

    Scene scene;
    for (auto& circle: circles) {
        scene.addCircle(circle.coords.x, circle.coords.y,circle.r, sf::Color::Red);
    }

    for (auto& circle: static_circles) {
        scene.addCircle(circle.coords.x, circle.coords.y,circle.r, sf::Color::Red);
    }

    double deltaTime = 1;

    while (scene.isOpen()) {

        for (auto& circle: circles) {
            circle.V = circle.V + circle.a * deltaTime;
            circle.coords = circle.coords + circle.V * deltaTime;
            scene.setCirclePosition(circle.index, circle);
        }



        for (int i = 0; i < circles.size(); i++) {
            for (int j = i + 1; j < circles.size(); j++) {
                if (sqrt
                       ((circles[i].coords.x - circles[j].coords.x) * (circles[i].coords.x - circles[j].coords.x) +
                       (circles[i].coords.y - circles[j].coords.y) * (circles[i].coords.y - circles[j].coords.y) +
                       (circles[i].coords.z - circles[j].coords.z) * (circles[i].coords.z - circles[j].coords.z)) < circles[i].r + circles[j].r
                       ){

                    Vector V1 = circles[i].V;
                    Vector V2 = circles[j].V;

                    circles[i].V = (V1 * (circles[i].m - circles[j].m) + V2 * 2 * circles[j].m)/(circles[i].m + circles[j].m);
                    circles[j].V = (V2 * (circles[j].m - circles[i].m) + V1 * 2 * circles[i].m)/(circles[i].m + circles[j].m);
                    circles[i].coords = circles[i].coords + circles[i].V * deltaTime;
                    circles[i].V = circles[i].V + circles[i].a * deltaTime;
                    scene.setCirclePosition(circles[i].index, circles[i]);

                    circles[j].coords = circles[j].coords + circles[j].V * deltaTime;
                    circles[j].V = circles[j].V + circles[j].a * deltaTime;
                    scene.setCirclePosition(circles[j].index, circles[j]);
                }
            }
        }

        for (int i = 0; i < circles.size(); i++) {
            for (int j = 0; j < static_circles.size(); j++) {
                if (sqrt
                       ((circles[i].coords.x - static_circles[j].coords.x) * (circles[i].coords.x - static_circles[j].coords.x) +
                       (circles[i].coords.y - static_circles[j].coords.y) * (circles[i].coords.y - static_circles[j].coords.y) +
                       (circles[i].coords.z - static_circles[j].coords.z) * (circles[i].coords.z - static_circles[j].coords.z)) < circles[i].r + static_circles[j].r
                       )
                    {

                    Vector normal = circles[i].coords - static_circles[j].coords;

                    normal = normal.normalize();

                    double velocityAlongNormal = circles[i].V.x * normal.x + circles[i].V.y * normal.y;

                    double impulse = (1.0 + 0.9) * velocityAlongNormal;

                    circles[i].V.x -= impulse * normal.x;
                    circles[i].V.y -= impulse * normal.y;

                    circles[i].coords = circles[i].coords + circles[i].V * deltaTime;
                    scene.setCirclePosition(circles[i].index, circles[i]);
                    }
            }
        }



        if (!scene.update()) break;

        sf::sleep(sf::milliseconds(16)); // ~60 FPS
    }
}
