#pragma once

#include "figure.h"
#include <iostream>
#include <utility>
#include <cmath>

class Hexagon : public Figure
{
public:
    // Конструктор по умолчанию устанавливает 6 вершин
    Hexagon();
    // Конструктор, принимающий массив вершин
    Hexagon(const std::pair<double, double>* arr);
    // Копирующий конструктор
    Hexagon(const Hexagon &other);
    // Перемещающий конструктор
    Hexagon(Hexagon &&other) noexcept;
    virtual ~Hexagon();

    Hexagon &operator=(const Hexagon &other);
    Hexagon &operator=(Hexagon &&other) noexcept;

    // Вычисление геометрического центра шестиугольника
    std::pair<double, double> geomcenter() override;
    // Оператор приведения к double возвращает площадь шестиугольника,
    // вычисляемую по формуле Гаусса
    explicit operator double() override;

    friend std::ostream &operator<<(std::ostream &os, Hexagon &f);
    friend std::istream &operator>>(std::istream &is, Hexagon &f);
};

std::ostream &operator<<(std::ostream &os, Hexagon &f);
std::istream &operator>>(std::istream &is, Hexagon &f);
