#pragma once
#include "point.h"
#include <memory>
#include <vector>
#include <iostream>
#include <stdexcept>

template<Scalar T>
class Figure {
public:
    virtual ~Figure() = default;
    // Оператор приведения к double вычисляет площадь фигуры
    virtual explicit operator double() const = 0;
    // Вычисление геометрического центра (возвращает умный указатель на Point)
    virtual std::unique_ptr<Point<T>> geomcenter() const = 0;
    // Чтение и вывод
    virtual void read(std::istream &is) = 0;
    virtual void print(std::ostream &os) const = 0;
    // Оператор сравнения
    virtual bool operator==(const Figure<T>& other) const = 0;

protected:
    // Хранение вершин в виде вектора умных указателей
    std::vector<std::unique_ptr<Point<T>>> points;
};

template<Scalar T>
std::ostream &operator<<(std::ostream &os, const Figure<T> &f) {
    f.print(os);
    return os;
}

template<Scalar T>
std::istream &operator>>(std::istream &is, Figure<T> &f) {
    f.read(is);
    return is;
}
