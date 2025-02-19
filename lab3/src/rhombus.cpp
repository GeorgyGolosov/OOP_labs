#include "../include/rhombus.h"
#include <iostream>
#include <cmath>

Rhombus::Rhombus() {
    cnt_vertex = 4;  // Для ромба всегда 4 вершины
    points = new std::pair<double, double>[cnt_vertex];
}

Rhombus::Rhombus(const std::pair<double, double>* arr) {
    cnt_vertex = 4;
    points = new std::pair<double, double>[cnt_vertex];
    for (int i = 0; i < cnt_vertex; i++) {
        points[i] = arr[i];
    }
}

Rhombus::Rhombus(const Rhombus &other) : Figure(other) {
    // cnt_vertex уже скопирован базовым конструктором; гарантируем, что он равен 4
    cnt_vertex = other.cnt_vertex;
}

Rhombus::Rhombus(Rhombus &&other) noexcept : Figure(std::move(other)) {
    // Перемещение происходит через базовый класс
}

Rhombus::~Rhombus() {
    // Освобождение памяти осуществляется в деструкторе базового класса Figure
}

Rhombus &Rhombus::operator=(const Rhombus &other) {
    if (this != &other)
        Figure::operator=(other);
    return *this;
}

Rhombus &Rhombus::operator=(Rhombus &&other) noexcept {
    if (this != &other)
        Figure::operator=(std::move(other));
    return *this;
}

std::pair<double, double> Rhombus::geomcenter() {
    // Вычисляем центр ромба как середину диагонали между вершинами 0 и 2
    return { (points[0].first + points[2].first) / 2.0,
             (points[0].second + points[2].second) / 2.0 };
}

Rhombus::operator double() {
    // Площадь ромба = (d1 * d2) / 2, где
    // d1 = расстояние между точками 0 и 2,
    // d2 = расстояние между точками 1 и 3
    double d1 = pt_dist(points[0], points[2]);
    double d2 = pt_dist(points[1], points[3]);
    return (d1 * d2) / 2.0;
}

std::ostream &operator<<(std::ostream &os, Rhombus &f) {
    for (int i = 0; i < f.cnt_vertex; ++i) {
        os << "(" << f.points[i].first << "," << f.points[i].second << ")";
        if (i != f.cnt_vertex - 1)
            os << ", ";
    }
    os << std::endl;
    return os;
}

std::istream &operator>>(std::istream &is, Rhombus &f) {
    std::cout << "Enter the vertices {X,Y} of the Rhombus in direct sequence:" << std::endl;
    for (int i = 0; i < f.cnt_vertex; ++i) {
        is >> f.points[i].first >> f.points[i].second;
    }
    return is;
}
