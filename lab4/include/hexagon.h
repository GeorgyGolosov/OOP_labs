#pragma once
#include "figure.h"
#include "point.h"
#include <iostream>
#include <utility>
#include <cmath>
#include <vector>
#include <memory>
#include <stdexcept>

template<Scalar T>
class Hexagon : public Figure<T> {
public:
    Hexagon() {
        this->points.resize(6);
        for(auto &p : this->points)
            p = std::make_unique<Point<T>>();
    }
    Hexagon(const std::vector<Point<T>>& pts) {
        if(pts.size() != 6)
            throw std::invalid_argument("Hexagon requires 6 points");
        this->points.resize(6);
        for (size_t i = 0; i < 6; i++){
            this->points[i] = std::make_unique<Point<T>>(pts[i].x, pts[i].y);
        }
    }
    Hexagon(const Hexagon<T>& other) {
        this->points.resize(6);
        for (size_t i = 0; i < 6; i++){
            this->points[i] = std::make_unique<Point<T>>(*(other.points[i]));
        }
    }
    Hexagon(Hexagon<T>&& other) noexcept = default;

    Hexagon<T>& operator=(const Hexagon<T>& other) {
        if(this != &other){
            for (size_t i = 0; i < 6; i++){
                *(this->points[i]) = *(other.points[i]);
            }
        }
        return *this;
    }
    Hexagon<T>& operator=(Hexagon<T>&& other) noexcept = default;

    virtual explicit operator double() const override {
        T area = 0;
        size_t n = this->points.size();
        for (size_t i = 0; i < n; i++){
            size_t j = (i+1) % n;
            area += this->points[i]->x * this->points[j]->y - this->points[j]->x * this->points[i]->y;
        }
        return std::abs(area)/2;
    }
    virtual std::unique_ptr<Point<T>> geomcenter() const override {
        T sumX = 0, sumY = 0;
        for(const auto &p: this->points){
            sumX += p->x;
            sumY += p->y;
        }
        return std::make_unique<Point<T>>(sumX/this->points.size(), sumY/this->points.size());
    }
    virtual void read(std::istream &is) override {
        for(auto &p : this->points)
            is >> *p;
    }
    virtual void print(std::ostream &os) const override {
        os << "Hexagon vertices: ";
        for(size_t i = 0; i < this->points.size(); i++){
            os << *this->points[i];
            if(i != this->points.size()-1) os << ", ";
        }
    }
    virtual bool operator==(const Figure<T>& other) const override {
        const Hexagon<T>* h = dynamic_cast<const Hexagon<T>*>(&other);
        if(!h) return false;
        for(size_t i = 0; i < this->points.size(); i++){
            if(!( *(this->points[i]) == *(h->points[i]) ))
                return false;
        }
        return true;
    }
};

template<Scalar T>
std::ostream &operator<<(std::ostream &os, const Hexagon<T>& h) {
    h.print(os);
    return os;
}

template<Scalar T>
std::istream &operator>>(std::istream &is, Hexagon<T>& h) {
    h.read(is);
    return is;
}
