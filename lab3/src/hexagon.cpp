#include "../include/hexagon.h"
#include <iostream>
#include <cmath>

Hexagon::Hexagon()
{
    cnt_vertex = 6;  // Устанавливаем правильное количество вершин
    points = new std::pair<double, double>[cnt_vertex];
}

Hexagon::Hexagon(const std::pair<double, double>* arr)
{
    cnt_vertex = 6;
    points = new std::pair<double, double>[cnt_vertex];
    for (int i = 0; i < cnt_vertex; i++)
    {
        points[i] = arr[i];
    }
}

Hexagon::Hexagon(const Hexagon &other) : Figure(other)
{
    cnt_vertex = other.cnt_vertex;  // Должно быть 6
}

Hexagon::Hexagon(Hexagon &&other) noexcept : Figure(std::move(other)) {}

Hexagon::~Hexagon() {}

Hexagon &Hexagon::operator=(const Hexagon &other)
{
    if (this != &other)
        Figure::operator=(other);
    return *this;
}

Hexagon &Hexagon::operator=(Hexagon &&other) noexcept
{
    Figure::operator=(std::move(other));
    return *this;
}

std::pair<double, double> Hexagon::geomcenter()
{
    double sumX = 0, sumY = 0;
    for (int i = 0; i < cnt_vertex; ++i)
    {
        sumX += points[i].first;
        sumY += points[i].second;
    }
    return { sumX / cnt_vertex, sumY / cnt_vertex };
}

Hexagon::operator double()
{
    double area = 0;
    for (int i = 0; i < cnt_vertex; ++i)
    {
        int j = (i + 1) % cnt_vertex;
        area += points[i].first * points[j].second - points[j].first * points[i].second;
    }
    return std::abs(area) / 2.0;
}

std::ostream &operator<<(std::ostream &os, Hexagon &f)
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

std::istream &operator>>(std::istream &is, Hexagon &f)
{
    std::cout << "Enter the vertices {X,Y} of the Hexagon in direct sequence." << '\n';
    for (int i = 0; i < f.cnt_vertex; ++i)
        is >> f.points[i].first >> f.points[i].second;
    return is;
}
