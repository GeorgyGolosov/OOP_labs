#include "../include/functions.h"
#include "../include/rhombus.h"
#include "../include/pentagon.h"
#include "../include/hexagon.h"
#include <iostream>

// Вывод всех фигур из массива
std::ostream &print(std::ostream &os, Figure **arr, int size) {
    for (int i = 0; i < size; i++) {
        if (arr[i] != nullptr) {
            os << "Figure " << i << ": " << *arr[i] << "\n";
        }
    }
    return os;
}

// Ввод фигур в массив
void input(Figure **arr, int count) {
    for (int i = 0; i < count; i++) {
        int choice;
        std::cout << "Select the type of figure for element " << i << ":\n";
        std::cout << "1 - Rhombus\n2 - Pentagon\n3 - Hexagon\nYour choice: ";
        std::cin >> choice;
        switch (choice) {
            case 1:
                arr[i] = new Rhombus();
                break;
            case 2:
                arr[i] = new Pentagon();
                break;
            case 3:
                arr[i] = new Hexagon();
                break;
            default:
                std::cout << "Invalid choice. Try again for this element.\n";
                i--;
                continue;
        }
        std::cout << "Enter the vertices of the figure (separated by space):\n";
        std::cin >> *arr[i];
    }
}

// Вывод геометрических центров для каждой фигуры
std::ostream &geomcenter(std::ostream &os, Figure **arr, int size) {
    for (int i = 0; i < size; i++) {
        if (arr[i] != nullptr) {
            auto center = arr[i]->geomcenter();
            os << "Geometric center of figure " << i << ": ("
               << center.first << ", " << center.second << ")\n";
        }
    }
    return os;
}

// Вывод площадей каждой фигуры
std::ostream &separate_areas(std::ostream &os, Figure **arr, int size) {
    for (int i = 0; i < size; i++) {
        if (arr[i] != nullptr) {
            double area = static_cast<double>(*arr[i]);
            os << "Area of figure " << i << ": " << area << "\n";
        }
    }
    return os;
}

// Вычисление суммарной площади фигур в массиве
double all_area(Figure **arr, int size) {
    double total = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] != nullptr) {
            total += static_cast<double>(*arr[i]);
        }
    }
    return total;
}

// Удаление фигуры по индексу из массива
void del(Figure **arr, int size) {
    int index;
    std::cout << "Enter the index of the figure to delete: ";
    std::cin >> index;
    if (index < 0 || index >= size || arr[index] == nullptr) {
        std::cout << "Invalid index.\n";
        return;
    }
    delete arr[index];
    // Сдвиг элементов влево
    for (int i = index; i < size - 1; i++) {
        arr[i] = arr[i + 1];
    }
    arr[size - 1] = nullptr;
    std::cout << "Figure deleted.\n";
}
