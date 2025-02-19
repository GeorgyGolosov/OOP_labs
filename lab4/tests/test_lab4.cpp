#include <gtest/gtest.h>
#include <sstream>
#include <vector>
#include <memory>
#include <cmath>
#include "../include/point.h"
#include "../include/figure.h"
#include "../include/rhombus.h"
#include "../include/pentagon.h"
#include "../include/hexagon.h"
#include "../include/array.h"

using std::vector;
using std::unique_ptr;

// ------------------------- Тесты для класса Point -------------------------
TEST(PointTest, DefaultConstructor) {
    Point<double> p;
    EXPECT_DOUBLE_EQ(p.x, 0.0);
    EXPECT_DOUBLE_EQ(p.y, 0.0);
}

TEST(PointTest, ParameterConstructor) {
    Point<double> p(3.0, 4.0);
    EXPECT_DOUBLE_EQ(p.x, 3.0);
    EXPECT_DOUBLE_EQ(p.y, 4.0);
}

TEST(PointTest, CopyConstructor) {
    Point<double> p1(3.0, 4.0);
    Point<double> p2(p1);
    EXPECT_DOUBLE_EQ(p2.x, 3.0);
    EXPECT_DOUBLE_EQ(p2.y, 4.0);
}

TEST(PointTest, AssignmentOperator) {
    Point<double> p1(3.0, 4.0);
    Point<double> p2;
    p2 = p1;
    EXPECT_DOUBLE_EQ(p2.x, 3.0);
    EXPECT_DOUBLE_EQ(p2.y, 4.0);
}

// ------------------------- Тесты для класса Rhombus -------------------------
TEST(RhombusTest, DefaultConstructor) {
    Rhombus<double> r;
    unique_ptr<Point<double>> center = r.geomcenter();
    EXPECT_NEAR(center->x, 0.0, 1e-6);
    EXPECT_NEAR(center->y, 0.0, 1e-6);
}

TEST(RhombusTest, AreaTest) {
    // Ромб с вершинами: (0,0), (1,1), (2,0), (1,-1)
    vector<Point<double>> pts = {
        Point<double>(0, 0),
        Point<double>(1, 1),
        Point<double>(2, 0),
        Point<double>(1, -1)
    };
    Rhombus<double> r(pts);
    // d1 = distance between (0,0) and (2,0) = 2, d2 = distance between (1,1) and (1,-1) = 2, площадь = 2
    EXPECT_NEAR(static_cast<double>(r), 2.0, 1e-6);
}

TEST(RhombusTest, GeomCenterTest) {
    vector<Point<double>> pts = {
        Point<double>(0, 0),
        Point<double>(1, 1),
        Point<double>(2, 0),
        Point<double>(1, -1)
    };
    Rhombus<double> r(pts);
    unique_ptr<Point<double>> center = r.geomcenter();
    EXPECT_NEAR(center->x, 1.0, 1e-6);
    EXPECT_NEAR(center->y, 0.0, 1e-6);
}

// ------------------------- Тесты для класса Pentagon -------------------------
TEST(PentagonTest, DefaultConstructor) {
    Pentagon<double> p;
    unique_ptr<Point<double>> center = p.geomcenter();
    EXPECT_NEAR(center->x, 0.0, 1e-6);
    EXPECT_NEAR(center->y, 0.0, 1e-6);
}

TEST(PentagonTest, AreaTest) {
    // Генерируем правильный пятиугольник с центром (0,0) и радиусом 1
    const double PI = std::acos(-1);
    vector<Point<double>> pts;
    for (int i = 0; i < 5; i++) {
        double angle = 2 * PI * i / 5;
        pts.push_back(Point<double>(std::cos(angle), std::sin(angle)));
    }
    Pentagon<double> p(pts);
    // Теоретическая площадь: (5/2)*r^2*sin(2π/5)
    double expected = (5.0 / 2.0) * 1.0 * 1.0 * std::sin(2 * PI / 5);
    EXPECT_NEAR(static_cast<double>(p), expected, 1e-6);
}

TEST(PentagonTest, GeomCenterTest) {
    const double PI = std::acos(-1);
    vector<Point<double>> pts;
    for (int i = 0; i < 5; i++) {
        double angle = 2 * PI * i / 5;
        pts.push_back(Point<double>(std::cos(angle), std::sin(angle)));
    }
    Pentagon<double> p(pts);
    unique_ptr<Point<double>> center = p.geomcenter();
    // Геометрический центр правильного пятиугольника должен быть (0,0)
    EXPECT_NEAR(center->x, 0.0, 1e-6);
    EXPECT_NEAR(center->y, 0.0, 1e-6);
}

// ------------------------- Тесты для класса Hexagon -------------------------
TEST(HexagonTest, DefaultConstructor) {
    Hexagon<double> h;
    unique_ptr<Point<double>> center = h.geomcenter();
    EXPECT_NEAR(center->x, 0.0, 1e-6);
    EXPECT_NEAR(center->y, 0.0, 1e-6);
}

TEST(HexagonTest, AreaTest) {
    // Генерируем правильный шестиугольник с центром (0,0) и радиусом 1
    const double PI = std::acos(-1);
    vector<Point<double>> pts;
    for (int i = 0; i < 6; i++) {
        double angle = 2 * PI * i / 6;
        pts.push_back(Point<double>(std::cos(angle), std::sin(angle)));
    }
    Hexagon<double> h(pts);
    double expected = (3 * std::sqrt(3) / 2) * 1.0 * 1.0; // ~2.598076211353316
    EXPECT_NEAR(static_cast<double>(h), expected, 1e-6);
}

TEST(HexagonTest, GeomCenterTest) {
    const double PI = std::acos(-1);
    vector<Point<double>> pts;
    for (int i = 0; i < 6; i++) {
        double angle = 2 * PI * i / 6;
        pts.push_back(Point<double>(std::cos(angle), std::sin(angle)));
    }
    Hexagon<double> h(pts);
    unique_ptr<Point<double>> center = h.geomcenter();
    EXPECT_NEAR(center->x, 0.0, 1e-6);
    EXPECT_NEAR(center->y, 0.0, 1e-6);
}

// ------------------------- Тесты для класса Array -------------------------
TEST(ArrayTest, PushAndAccess) {
    Array<int> arr(2);
    arr.push_back(10);
    arr.push_back(20);
    EXPECT_EQ(arr.size(), 2);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
    arr.push_back(30);
    EXPECT_EQ(arr.size(), 3);
    EXPECT_EQ(arr[2], 30);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
