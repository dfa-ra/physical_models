//
// Created by ra on 04.11.24.
//

#ifndef VEC_H
#define VEC_H



#include <math.h>
#include <ostream>
#include <stdio.h>

class Vector {
public:
    long double x;
    long double y;
    long double z;

    explicit Vector(
        const long double x = 0.0,
        const long double y = 0.0,
        const long double z = 0.0)
            : x(x), y(y), z(z) {}

    [[nodiscard]] long double len() const {
        return hypot(hypot(this->x, this->y), this->z);
    }

    void vec_norm();

    ~Vector();

    // Сложение векторов
    Vector operator+(const Vector& other) const {
        return Vector{std::fma(x, 1.0L, other.x), std::fma(y, 1.0L, other.y), std::fma(z, 1.0L, other.z)};
    }

    Vector operator-() const {
        return Vector{-x, -y, -z};
    }

    // Вычитание векторов
    Vector operator-(const Vector& other) const {
        return *this + (-other);
    }

    // Скалярное произведение
    long double operator*(const Vector& other) const {
        return std::fma(x, other.x, std::fma(y, other.y, z * other.z));
    }

    // Векторное произведение
    Vector operator^(const Vector& other) const {
        return Vector{
            std::fma(y, other.z, -z * other.y),
            std::fma(z, other.x, -x * other.z),
            std::fma(x, other.y, -y * other.x)
        };
    }

    // Умножение на скаляр
    Vector operator*(long double k) const {
        return Vector{k * x, k * y, k * z};
    }

    // Деление на скаляр
    Vector operator/(long double k) const {
        return Vector{x / k, y / k, z / k};
    }

    // Длина вектора
    [[nodiscard]] long double length() const {
        return std::sqrt(*this * *this);
    }

    // Нормализация вектора
    [[nodiscard]] Vector normalize() const {
        long double len = length();
        return (len > 0) ? *this / len : Vector{0, 0, 0};
    }

    // Вывод вектора
    friend std::ostream& operator<<(std::ostream& os, const Vector& v) {
        return os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    }

};

#endif //VEC_H
