#include <gtest/gtest.h>
#include <cmath>
#include <vector>
#include "rhombus.h"
#include "pentagon.h"
#include "hexagon.h"

using std::pair;
using std::vector;

// Тесты для класса Rhombus
TEST(RhombusTest, InitializationTest) {
    // Создаем массив вершин ромба: (0,0), (1,1), (2,0), (1,-1)
    vector<pair<double, double>> rhombusPoints = {
        {0, 0},
        {1, 1},
        {2, 0},
        {1, -1}
    };

    // Проверяем, что объект можно создать без исключений
    EXPECT_NO_THROW({
        Rhombus r(rhombusPoints.data());
    });
}

TEST(RhombusTest, AreaTest) {
    vector<pair<double, double>> rhombusPoints = {
        {0, 0},
        {1, 1},
        {2, 0},
        {1, -1}
    };

    Rhombus r(rhombusPoints.data());
    // Площадь ромба должна равняться 2: d1 = distance between (0,0) и (2,0) = 2, d2 = distance between (1,1) и (1,-1) = 2, area = 2*2/2 = 2.
    EXPECT_NEAR(double(r), 2.0, 1e-6);
}

TEST(RhombusTest, GeomCenterTest) {
    vector<pair<double, double>> rhombusPoints = {
        {0, 0},
        {1, 1},
        {2, 0},
        {1, -1}
    };

    Rhombus r(rhombusPoints.data());
    pair<double, double> center = r.geomcenter();
    // Геометрический центр вычисляется как точка между вершинами 0 и 2:
    // ((0-2)/2 + 2, (0-0)/2 + 0) = (1, 0)
    EXPECT_NEAR(center.first, 1.0, 1e-6);
    EXPECT_NEAR(center.second, 0.0, 1e-6);
}

// Если необходимо, можно добавить тест на некорректный набор точек,
// но в текущей реализации проверок на валидность точек нет.
// Поэтому данный тест можно закомментировать или доработать реализацию.
// TEST(RhombusTest, InvalidPointsTest) {
//     vector<pair<double, double>> invalidPoints = {
//         {0, 0},
//         {1, 1},
//         {2, 2},
//         {3, 3}
//     };
//     EXPECT_THROW(Rhombus r(invalidPoints.data()), std::invalid_argument);
// }

// Вспомогательная функция для генерации вершин правильного многоугольника
vector<pair<double, double>> generateRegularPolygonVertices(int n, pair<double, double> center, double radius) {
    vector<pair<double, double>> vertices(n);
    const double PI = std::acos(-1.0);
    for (int i = 0; i < n; i++) {
        double angle = 2 * PI * i / n;
        vertices[i] = { center.first + radius * std::cos(angle),
                        center.second + radius * std::sin(angle) };
    }
    return vertices;
}

// Тесты для класса Hexagon
TEST(HexagonTest, AreaTest) {
    pair<double, double> center = {0, 0};
    double radius = 1.0;
    // Генерируем вершины правильного шестиугольника
    auto vertices = generateRegularPolygonVertices(6, center, radius);
    Hexagon h(vertices.data());
    // Площадь правильного шестиугольника: (3 * sqrt(3) / 2) * radius^2
    double expectedArea = (3 * std::sqrt(3) / 2) * radius * radius;
    EXPECT_NEAR(double(h), expectedArea, 1e-6);
}

TEST(HexagonTest, GeomCenterTest) {
    pair<double, double> center = {0, 0};
    double radius = 1.0;
    auto vertices = generateRegularPolygonVertices(6, center, radius);
    Hexagon h(vertices.data());
    pair<double, double> computedCenter = h.geomcenter();
    EXPECT_NEAR(computedCenter.first, center.first, 1e-6);
    EXPECT_NEAR(computedCenter.second, center.second, 1e-6);
}

// Тесты для класса Pentagon
TEST(PentagonTest, AreaTest) {
    pair<double, double> center = {0, 0};
    double radius = 1.0;
    auto vertices = generateRegularPolygonVertices(5, center, radius);
    Pentagon p(vertices.data());
    // Площадь правильного пятиугольника: (5/2) * radius^2 * sin(2*pi/5)
    double expectedArea = (5.0 / 2.0) * radius * radius * std::sin(2 * M_PI / 5);
    EXPECT_NEAR(double(p), expectedArea, 1e-6);
}

TEST(PentagonTest, GeomCenterTest) {
    pair<double, double> center = {0, 0};
    double radius = 1.0;
    auto vertices = generateRegularPolygonVertices(5, center, radius);
    Pentagon p(vertices.data());
    pair<double, double> computedCenter = p.geomcenter();
    EXPECT_NEAR(computedCenter.first, center.first, 1e-6);
    EXPECT_NEAR(computedCenter.second, center.second, 1e-6);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
