#pragma once

#include "figure.h"
#include "rhombus.h"
#include "pentagon.h"
#include "hexagon.h"

std::ostream &print(std::ostream &os, Figure **arr, int size);
void input(Figure **arr, int count);
std::ostream &geomcenter(std::ostream &os, Figure **arr, int size);     // Вывод геометрических центров фигур
std::ostream &separate_areas(std::ostream &os, Figure **arr, int size); // Вывод площадей каждой фигуры
double all_area(Figure **arr, int size);                                // Суммарная площадь фигур
void del(Figure **arr, int size);                                         // Удаление фигуры по индексу
