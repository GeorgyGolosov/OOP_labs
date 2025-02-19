#include "figure.h"

Figure::Figure() {
    // По умолчанию cnt_vertex = 4
    points = new std::pair<double,double>[cnt_vertex];
}

Figure::Figure(const Figure &other) : cnt_vertex(other.cnt_vertex) {
    points = new std::pair<double,double>[cnt_vertex];
    for (int i = 0; i < cnt_vertex; i++) {
        points[i] = other.points[i];
    }
}

Figure::Figure(const std::pair<double, double>* arr) {
    points = new std::pair<double,double>[cnt_vertex];
    for (int i = 0; i < cnt_vertex; i++) {
        points[i] = arr[i];
    }
}

Figure::~Figure() {
    delete[] points;
}

Figure::operator double() {
    // Базовая реализация не вычисляет площадь
    return 0.0;
}

std::pair<double, double> Figure::geomcenter() {
    double sumX = 0, sumY = 0;
    for (int i = 0; i < cnt_vertex; i++) {
        sumX += points[i].first;
        sumY += points[i].second;
    }
    return {sumX / cnt_vertex, sumY / cnt_vertex};
}

bool Figure::operator==(const Figure &right) const {
    if (cnt_vertex != right.cnt_vertex)
        return false;
    for (int i = 0; i < cnt_vertex; i++) {
        if (points[i] != right.points[i])
            return false;
    }
    return true;
}

Figure &Figure::operator=(const Figure &right_operand) {
    if (this == &right_operand)
        return *this;
    if (cnt_vertex != right_operand.cnt_vertex) {
        delete[] points;
        cnt_vertex = right_operand.cnt_vertex;
        points = new std::pair<double,double>[cnt_vertex];
    }
    for (int i = 0; i < cnt_vertex; i++) {
        points[i] = right_operand.points[i];
    }
    return *this;
}

Figure &Figure::operator=(Figure &&right_operand) {
    if (this == &right_operand)
        return *this;
    delete[] points;
    cnt_vertex = right_operand.cnt_vertex;
    points = right_operand.points;
    right_operand.points = nullptr;
    return *this;
}

double Figure::pt_dist(std::pair<double, double> &p1, std::pair<double, double> &p2) {
    double dx = p1.first - p2.first;
    double dy = p1.second - p2.second;
    return std::sqrt(dx*dx + dy*dy);
}

std::ostream &operator<<(std::ostream &os, Figure &f) {
    os << "Vertices: ";
    for (int i = 0; i < f.cnt_vertex; i++) {
        os << "(" << f.points[i].first << ", " << f.points[i].second << ") ";
    }
    return os;
}

std::istream &operator>>(std::istream &is, Figure &f) {
    for (int i = 0; i < f.cnt_vertex; i++) {
        is >> f.points[i].first >> f.points[i].second;
    }
    return is;
}
