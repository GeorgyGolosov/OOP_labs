#pragma once
#include "figure.h"
#include "rhombus.h"
#include "pentagon.h"
#include "hexagon.h"
#include "array.h"
#include <iostream>
#include <memory>

// Здесь Array хранит умные указатели на Figure<T>
template<typename T>
std::ostream &print(std::ostream &os, const Array<std::shared_ptr<Figure<T>>>& arr) {
    for(size_t i = 0; i < arr.size(); i++){
         os << "Figure " << i << ": " << *arr[i] << "\n";
    }
    return os;
}

template<typename T>
void input(Array<std::shared_ptr<Figure<T>>>& arr) {
    size_t count;
    std::cout << "Type count of figures: ";
    std::cin >> count;
    for(size_t i = 0; i < count; i++){
         int choice;
         std::cout << "Select the type of figure for element " << i << ":\n";
         std::cout << "1 - Rhombus\n2 - Pentagon\n3 - Hexagon\nYour choice: ";
         std::cin >> choice;
         std::shared_ptr<Figure<T>> fig;
         if(choice == 1){
             fig = std::make_shared<Rhombus<T>>();
         } else if(choice == 2){
             fig = std::make_shared<Pentagon<T>>();
         } else if(choice == 3){
             fig = std::make_shared<Hexagon<T>>();
         } else {
             std::cout << "Invalid choice. Try again.\n";
             i--;
             continue;
         }
         std::cout << "Enter the vertices of the figure (separated by space):\n";
         std::cin >> *fig;
         arr.push_back(fig);
    }
}

template<typename T>
std::ostream &geomcenter(std::ostream &os, const Array<std::shared_ptr<Figure<T>>>& arr) {
    for(size_t i = 0; i < arr.size(); i++){
         auto center = arr[i]->geomcenter();
         os << "Geometric center of figure " << i << ": " << *center << "\n";
    }
    return os;
}

template<typename T>
std::ostream &separate_areas(std::ostream &os, const Array<std::shared_ptr<Figure<T>>>& arr) {
    for(size_t i = 0; i < arr.size(); i++){
         os << "Area of figure " << i << ": " << static_cast<double>(*arr[i]) << "\n";
    }
    return os;
}

template<typename T>
double all_area(const Array<std::shared_ptr<Figure<T>>>& arr) {
    double total = 0;
    for(size_t i = 0; i < arr.size(); i++){
         total += static_cast<double>(*arr[i]);
    }
    return total;
}

template<typename T>
void del(Array<std::shared_ptr<Figure<T>>>& arr) {
    size_t index;
    std::cout << "Enter the index of the figure to delete: ";
    std::cin >> index;
    if(index >= arr.size()){
         std::cout << "Invalid index.\n";
         return;
    }
    arr.remove(index);
    std::cout << "Figure deleted.\n";
}
