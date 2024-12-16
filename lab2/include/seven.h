#pragma once

#include <iostream>
#include <string>
#include <stdexcept>

class Seven {
public:
    // Конструкторы
    Seven(); // Конструктор по умолчанию
    Seven(const size_t &n, unsigned char t = 0); // Заполняющий конструктор
    Seven(const std::initializer_list<unsigned char> &t); // Конструктор со списком инициализации
    Seven(const std::string &t); // Конструктор из строки
    Seven(const Seven &other); // Конструктор копирования
    Seven(Seven &&other) noexcept; // Конструктор перемещения
    ~Seven() noexcept; // Деструктор

    // Методы
    void print() const; // Печать числа
    size_t size() const; // Возвращает размер числа

    // Арифметические операции
    Seven operator+(const Seven &other) const;
    Seven operator-(const Seven &other) const;
    Seven& operator+=(const Seven &other);
    Seven& operator-=(const Seven &other);

    // Операции сравнения
    bool operator==(const Seven &other) const;
    bool operator!=(const Seven &other) const;
    bool operator<(const Seven &other) const;
    bool operator>(const Seven &other) const;
    bool operator<=(const Seven &other) const;
    bool operator>=(const Seven &other) const;

    // Операторы присваивания
    Seven& operator=(const Seven &other);
    Seven& operator=(Seven &&other) noexcept;

private:
    size_t _size; // Размер массива
    unsigned char *_array; // Динамический массив семеричных цифр

    void validateSevenNumber(const std::string &t); // Проверка строки на корректность семеричного числа
    void clean(); // Очистка массива
};
