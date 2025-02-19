#pragma once
#include <iostream>
#include <utility>
#include <cmath>

class Figure
{
public:
    Figure();
    Figure(const Figure &other);
    Figure(const std::pair<double, double>* arr);
    virtual ~Figure();

    // Виртуальный оператор приведения к типу double – вычисление площади
    virtual explicit operator double();
    // Вычисление геометрического центра фигуры
    virtual std::pair<double, double> geomcenter();

    bool operator==(const Figure &right) const;
    Figure &operator=(const Figure &right_operand);
    Figure &operator=(Figure &&right_operand);

protected:
    std::pair<double, double>* points;
    int cnt_vertex = 4;  // По умолчанию 4 вершины

    // Вспомогательная функция для вычисления расстояния между двумя точками
    double pt_dist(std::pair<double, double> &p1, std::pair<double, double> &p2);

    friend std::ostream &operator<<(std::ostream &os, Figure &f);
    friend std::istream &operator>>(std::istream &is, Figure &f);
};

std::ostream &operator<<(std::ostream &os, Figure &f);
std::istream &operator>>(std::istream &is, Figure &f);
