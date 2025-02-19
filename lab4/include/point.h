#pragma once
#include <concepts>
#include <iostream>
#include <type_traits>
#include <cmath>

// Concept, проверяющий, что тип T является арифметическим (скалярным)
template<typename T>
concept Scalar = std::is_arithmetic_v<T>;

template<Scalar T>
class Point {
public:
    T x;
    T y;

    Point() : x(T()), y(T()) {}
    Point(T x_, T y_) : x(x_), y(y_) {}

    bool operator==(const Point &other) const {
        return x == other.x && y == other.y;
    }
};

template<Scalar T>
std::ostream &operator<<(std::ostream &os, const Point<T>& pt) {
    os << "(" << pt.x << ", " << pt.y << ")";
    return os;
}

template<Scalar T>
std::istream &operator>>(std::istream &is, Point<T>& pt) {
    is >> pt.x >> pt.y;
    return is;
}
