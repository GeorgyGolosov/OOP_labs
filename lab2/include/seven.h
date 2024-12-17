#pragma once

#include <iostream>
#include <string>
#include <stdexcept>

class Seven {
public:
    Seven();
    Seven(size_t n, unsigned char t = 0);
    Seven(const std::string &t);
    Seven(const Seven& other);                   // Конструктор копирования
    Seven(Seven&& other) noexcept;               // Конструктор перемещения
    Seven& operator=(const Seven& other);        // Оператор присваивания копированием
    Seven& operator=(Seven&& other) noexcept;    // Оператор присваивания перемещением
    ~Seven() noexcept;                           // Деструктор

    Seven operator+(const Seven& other) const;
    Seven operator-(const Seven& other) const;

    bool operator==(const Seven& other) const;
    bool operator<(const Seven& other) const;
    bool operator>(const Seven& other) const;
    void print(std::ostream& os) const;

private:
    size_t _size;
    unsigned char* _array;
};
