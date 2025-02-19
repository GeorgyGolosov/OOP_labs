#include "../include/pentagon.h"
#include <iostream>
#include <cmath>

Pentagon::Pentagon()
{
    cnt_vertex = 5;  // Устанавливаем правильное количество вершин
    points = new std::pair<double, double>[cnt_vertex];
}

Pentagon::Pentagon(const std::pair<double, double>* arr)
{
    cnt_vertex = 5;
    points = new std::pair<double, double>[cnt_vertex];
    for (int i = 0; i < cnt_vertex; i++)
    {
        points[i] = arr[i];
    }
}

Pentagon::Pentagon(const Pentagon &other) : Figure(other)
{
    cnt_vertex = other.cnt_vertex;  // Должно быть 5
}

Pentagon::Pentagon(Pentagon &&other) noexcept : Figure(std::move(other)) {}

Pentagon::~Pentagon() {}

Pentagon &Pentagon::operator=(const Pentagon &other)
{
    if (this != &other)
        Figure::operator=(other);
    return *this;
}

Pentagon &Pentagon::operator=(Pentagon &&other) noexcept
{
    Figure::operator=(std::move(other));
    return *this;
}

std::pair<double, double> Pentagon::geomcenter()
{
    double sumX = 0, sumY = 0;
    for (int i = 0; i < cnt_vertex; ++i)
    {
        sumX += points[i].first;
        sumY += points[i].second;
    }
    return { sumX / cnt_vertex, sumY / cnt_vertex };
}

Pentagon::operator double()
{
    double area = 0;
    for (int i = 0; i < cnt_vertex; ++i)
    {
        int j = (i + 1) % cnt_vertex;
        area += points[i].first * points[j].second - points[j].first * points[i].second;
    }
    return std::abs(area) / 2.0;
}

std::ostream &operator<<(std::ostream &os, Pentagon &f)
{
    for (int i = 0; i < f.cnt_vertex; ++i)
    {
        os << "(" << f.points[i].first << ',' << f.points[i].second << ')';
        if (i != f.cnt_vertex - 1)
            os << ", ";
    }
    os << '\n';
    return os;
}

std::istream &operator>>(std::istream &is, Pentagon &f)
{
    std::cout << "Enter the vertices {X,Y} of the Pentagon in direct sequence." << '\n';
    for (int i = 0; i < f.cnt_vertex; ++i)
        is >> f.points[i].first >> f.points[i].second;
    return is;
}
