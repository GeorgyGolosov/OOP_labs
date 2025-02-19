#pragma once
#include "figure.h"
#include "point.h"
#include <iostream>
#include <vector>
#include <memory>
#include <cmath>

template<Scalar T>
class Rhombus : public Figure<T> {
public:
    // Конструктор по умолчанию: создаёт ромб с 4 вершинами, инициализированными (0,0)
    Rhombus() {
         this->points.resize(4);
         for(auto &p: this->points)
             p = std::make_unique<Point<T>>();
    }
    // Конструктор с вектором точек
    Rhombus(const std::vector<Point<T>>& pts) {
         if(pts.size() != 4)
             throw std::invalid_argument("Rhombus requires 4 points");
         this->points.resize(4);
         for (size_t i = 0; i < 4; i++){
             this->points[i] = std::make_unique<Point<T>>(pts[i].x, pts[i].y);
         }
    }
    // Копирующий конструктор
    Rhombus(const Rhombus<T>& other) {
         this->points.resize(4);
         for (size_t i = 0; i < 4; i++){
             this->points[i] = std::make_unique<Point<T>>(*(other.points[i]));
         }
    }
    // Перемещающий конструктор
    Rhombus(Rhombus<T>&& other) noexcept = default;

    Rhombus<T>& operator=(const Rhombus<T>& other) {
         if(this != &other){
              for (size_t i = 0; i < 4; i++){
                   *(this->points[i]) = *(other.points[i]);
              }
         }
         return *this;
    }
    Rhombus<T>& operator=(Rhombus<T>&& other) noexcept = default;

    // Площадь ромба = (d1 * d2) / 2, где d1 – расстояние между точками 0 и 2, d2 – между точками 1 и 3.
    virtual explicit operator double() const override {
         T d1 = distance(*(this->points[0]), *(this->points[2]));
         T d2 = distance(*(this->points[1]), *(this->points[3]));
         return std::abs((d1 * d2) / 2);
    }
    // Геометрический центр вычисляется как средняя точка между вершинами 0 и 2.
    virtual std::unique_ptr<Point<T>> geomcenter() const override {
         T cx = (this->points[0]->x + this->points[2]->x) / 2;
         T cy = (this->points[0]->y + this->points[2]->y) / 2;
         return std::make_unique<Point<T>>(cx, cy);
    }
    virtual void read(std::istream &is) override {
         for(auto &p : this->points)
              is >> *p;
    }
    virtual void print(std::ostream &os) const override {
         os << "Rhombus vertices: ";
         for (size_t i = 0; i < this->points.size(); i++){
              os << *this->points[i];
              if(i != this->points.size()-1) os << ", ";
         }
    }
    virtual bool operator==(const Figure<T>& other) const override {
         const Rhombus<T>* r = dynamic_cast<const Rhombus<T>*>(&other);
         if(!r) return false;
         for (size_t i = 0; i < this->points.size(); i++){
              if(!( *(this->points[i]) == *(r->points[i]) ))
                   return false;
         }
         return true;
    }

private:
    T distance(const Point<T>& a, const Point<T>& b) const {
         T dx = a.x - b.x;
         T dy = a.y - b.y;
         return std::sqrt(dx*dx + dy*dy);
    }
};

template<Scalar T>
std::ostream &operator<<(std::ostream &os, const Rhombus<T>& r) {
    r.print(os);
    return os;
}

template<Scalar T>
std::istream &operator>>(std::istream &is, Rhombus<T>& r) {
    r.read(is);
    return is;
}
