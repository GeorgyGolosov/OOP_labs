#include "../include/seven.h"

// Конструктор по умолчанию
Seven::Seven() : _size(0), _array(nullptr) {}

// Конструктор с заданием размера и значения по умолчанию
Seven::Seven(size_t n, unsigned char t) : _size(n) {
    if (t >= 7) throw std::invalid_argument("Sevenary digits must be less than 7"); // Проверка на допустимые цифры
    _array = new unsigned char[n];
    for (size_t i = 0; i < n; ++i) {
        _array[i] = t;
    }
}

// Конструктор из строки
Seven::Seven(const std::string& t) : _size(t.size()) {
    _array = new unsigned char[_size];
    for (size_t i = 0; i < _size; ++i) {
        // Проверка на корректность семеричных цифр
        if (t[_size - i - 1] < '0' || t[_size - i - 1] > '6') {
            throw std::invalid_argument("Sevenary digits must be in range 0-6");
        }
        _array[i] = t[_size - i - 1] - '0';
    }
}

// Конструктор копирования
Seven::Seven(const Seven& other) : _size(other._size), _array(new unsigned char[other._size]) {
    for (size_t i = 0; i < _size; ++i) {
        _array[i] = other._array[i]; // Копирование массива
    }
}

// Конструктор перемещения
Seven::Seven(Seven&& other) noexcept : _size(other._size), _array(other._array) {
    other._size = 0;
    other._array = nullptr; // Передача владения ресурсами
}

// Деструктор
Seven::~Seven() noexcept {
    delete[] _array; // Освобождение памяти
}

// Оператор присваивания копированием
Seven& Seven::operator=(const Seven& other) {
    if (this == &other) return *this; // Защита от самоприсваивания

    delete[] _array; // Удаляем текущие ресурсы

    _size = other._size;
    _array = new unsigned char[_size];
    for (size_t i = 0; i < _size; ++i) {
        _array[i] = other._array[i]; // Копирование данных
    }

    return *this;
}

// Оператор присваивания перемещением
Seven& Seven::operator=(Seven&& other) noexcept {
    if (this == &other) return *this; // Защита от самоприсваивания

    delete[] _array; // Удаляем текущие ресурсы

    _size = other._size;
    _array = other._array;

    other._size = 0;
    other._array = nullptr; // Передача владения ресурсами

    return *this;
}

// Сложение
Seven Seven::operator+(const Seven& other) const {
    size_t maxSize = std::max(_size, other._size);  // Определяем максимальный размер
    unsigned char carry = 0;  // Перенос
    Seven result(maxSize + 1);  // Результат с запасом для возможного переноса

    size_t i = 0;
    for (; i < maxSize || carry; ++i) {
        unsigned char digitSum = carry;

        // Сложение цифр с текущей позиции в обоих числах
        if (i < _size) digitSum += _array[i];
        if (i < other._size) digitSum += other._array[i];

        result._array[i] = digitSum % 7;  // Остаток от деления на 7
        carry = digitSum / 7;  // Перенос (если сумма больше или равна 7)
    }

    // Устанавливаем точный размер результата (без лишних нулей)
    result._size = i;
    return result;
}


// Вычитание
Seven Seven::operator-(const Seven& other) const {
    if (*this < other) {
        throw std::invalid_argument("Result of subtraction cannot be negative"); // Результат не может быть отрицательным
    }

    Seven result(_size);
    unsigned char borrow = 0; // Заём

    for (size_t i = 0; i < _size; ++i) {
        unsigned char digitDiff = _array[i] - borrow; // Вычитаем заём
        if (i < other._size) digitDiff -= other._array[i];
        borrow = (digitDiff > _array[i]) ? 1 : 0; // Определяем, нужен ли заём
        result._array[i] = (borrow) ? digitDiff + 7 : digitDiff;
    }

    // Удаляем ведущие нули
    while (result._size > 0 && result._array[result._size - 1] == 0) {
        --result._size;
    }

    return result;
}

// Операторы сравнений
// Равенство
bool Seven::operator==(const Seven& other) const {
    if (_size != other._size) return false; // Размеры должны совпадать
    for (size_t i = 0; i < _size; ++i) {
        if (_array[i] != other._array[i]) return false; // Проверяем каждый элемент
    }
    return true;
}

// Меньше
bool Seven::operator<(const Seven& other) const {
    if (_size != other._size) return _size < other._size; // Сравниваем размеры
    for (size_t i = _size; i-- > 0;) {
        if (_array[i] != other._array[i]) {
            return _array[i] < other._array[i]; // Сравниваем старшие разряды
        }
    }
    return false;
}

// Больше
bool Seven::operator>(const Seven& other) const {
    return !(*this < other) && !(*this == other);
}

// Вывод
void Seven::print(std::ostream& os) const {
    for (size_t i = _size; i-- > 0;) {
        os << static_cast<char>(_array[i] + '0');
    }
}
