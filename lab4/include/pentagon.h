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
class Pentagon : public Figure<T> {
public:
    Pentagon() {
        this->points.resize(5);
        for(auto &p : this->points)
            p = std::make_unique<Point<T>>();
    }
    Pentagon(const std::vector<Point<T>>& pts) {
        if(pts.size() != 5)
            throw std::invalid_argument("Pentagon requires 5 points");
        this->points.resize(5);
        for (size_t i = 0; i < 5; i++){
            this->points[i] = std::make_unique<Point<T>>(pts[i].x, pts[i].y);
        }
    }
    Pentagon(const Pentagon<T>& other) {
        this->points.resize(5);
        for (size_t i = 0; i < 5; i++){
            this->points[i] = std::make_unique<Point<T>>(*(other.points[i]));
        }
    }
    Pentagon(Pentagon<T>&& other) noexcept = default;

    Pentagon<T>& operator=(const Pentagon<T>& other) {
        if(this != &other){
            for (size_t i = 0; i < 5; i++){
                *(this->points[i]) = *(other.points[i]);
            }
        }
        return *this;
    }
    Pentagon<T>& operator=(Pentagon<T>&& other) noexcept = default;

    virtual explicit operator double() const override {
        T area = 0;
        size_t n = this->points.size();
        for (size_t i = 0; i < n; i++){
            size_t j = (i + 1) % n;
            area += this->points[i]->x * this->points[j]->y - this->points[j]->x * this->points[i]->y;
        }
        return std::abs(area)/2;
    }
    virtual std::unique_ptr<Point<T>> geomcenter() const override {
        T sumX = 0, sumY = 0;
        for (const auto &p : this->points) {
            sumX += p->x;
            sumY += p->y;
        }
        return std::make_unique<Point<T>>(sumX / this->points.size(), sumY / this->points.size());
    }
    virtual void read(std::istream &is) override {
        for(auto &p : this->points)
            is >> *p;
    }
    virtual void print(std::ostream &os) const override {
        os << "Pentagon vertices: ";
        for (size_t i = 0; i < this->points.size(); i++){
            os << *this->points[i];
            if(i != this->points.size()-1) os << ", ";
        }
    }
    virtual bool operator==(const Figure<T>& other) const override {
        const Pentagon<T>* p = dynamic_cast<const Pentagon<T>*>(&other);
        if(!p) return false;
        for (size_t i = 0; i < this->points.size(); i++){
            if(!( *(this->points[i]) == *(p->points[i]) ))
                return false;
        }
        return true;
    }
};

template<Scalar T>
std::ostream &operator<<(std::ostream &os, const Pentagon<T> &p) {
    p.print(os);
    return os;
}

template<Scalar T>
std::istream &operator>>(std::istream &is, Pentagon<T> &p) {
    p.read(is);
    return is;
}
