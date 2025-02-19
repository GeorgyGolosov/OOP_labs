#pragma once

#include "figure.h"
#include <iostream>
#include <utility>
#include <cmath>

class Rhombus : public Figure
{
public:
    // Конструктор по умолчанию устанавливает 4 вершины
    Rhombus();
    // Конструктор, принимающий массив вершин (ожидается массив из 4 вершин)
    Rhombus(const std::pair<double, double>* arr);
    // Копирующий конструктор
    Rhombus(const Rhombus &other);
    // Перемещающий конструктор
    Rhombus(Rhombus &&other) noexcept;
    virtual ~Rhombus();

    Rhombus &operator=(const Rhombus &other);
    Rhombus &operator=(Rhombus &&other) noexcept;

    // Вычисление геометрического центра ромба (точка посередине между вершинами 0 и 2)
    std::pair<double, double> geomcenter() override;
    // Оператор приведения к типу double возвращает площадь ромба:
    // (d1 * d2) / 2, где d1 – расстояние между точками 0 и 2, d2 – между точками 1 и 3
    explicit operator double() override;

    friend std::ostream &operator<<(std::ostream &os, Rhombus &f);
    friend std::istream &operator>>(std::istream &is, Rhombus &f);
};

std::ostream &operator<<(std::ostream &os, Rhombus &f);
std::istream &operator>>(std::istream &is, Rhombus &f);
