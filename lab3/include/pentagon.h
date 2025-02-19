#pragma once

#include "figure.h"
#include <iostream>
#include <utility>
#include <cmath>

class Pentagon : public Figure
{
public:
    // Конструктор по умолчанию устанавливает 5 вершин
    Pentagon();
    // Конструктор, принимающий массив вершин
    Pentagon(const std::pair<double, double>* arr);
    // Копирующий конструктор
    Pentagon(const Pentagon &other);
    // Перемещающий конструктор
    Pentagon(Pentagon &&other) noexcept;
    virtual ~Pentagon();

    Pentagon &operator=(const Pentagon &other);
    Pentagon &operator=(Pentagon &&other) noexcept;

    // Вычисление геометрического центра пятиугольника (среднее арифметическое всех вершин)
    std::pair<double, double> geomcenter() override;
    // Оператор приведения к double возвращает площадь, вычисляемую по формуле Гаусса
    explicit operator double() override;

    friend std::ostream &operator<<(std::ostream &os, Pentagon &f);
    friend std::istream &operator>>(std::istream &is, Pentagon &f);
};

std::ostream &operator<<(std::ostream &os, Pentagon &f);
std::istream &operator>>(std::istream &is, Pentagon &f);
