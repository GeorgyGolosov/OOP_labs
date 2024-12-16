#include "../include/seven.h"

// --- Конструкторы ---
Seven::Seven() : _size(0), _array(nullptr) {}

Seven::Seven(const size_t &n, unsigned char t) {
    if (t >= 7) throw std::invalid_argument("Only digits 0-6 are allowed.");
    _size = n;
    _array = new unsigned char[_size];
    for (size_t i = 0; i < _size; ++i) {
        _array[i] = t;
    }
}

Seven::Seven(const std::initializer_list<unsigned char> &t) : _size(t.size()) {
    _array = new unsigned char[_size];
    size_t i = 0;
    for (unsigned char c : t) {
        if (c >= 7) throw std::invalid_argument("Only digits 0-6 are allowed.");
        _array[i++] = c;
    }
}

Seven::Seven(const std::string &t) {
    validateSevenNumber(t);
    _size = t.size();
    _array = new unsigned char[_size];
    for (size_t i = 0; i < _size; ++i) {
        _array[i] = t[_size - 1 - i] - '0'; // Строка хранится в обратном порядке
    }
}

Seven::Seven(const Seven &other) : _size(other._size) {
    _array = new unsigned char[_size];
    for (size_t i = 0; i < _size; ++i) {
        _array[i] = other._array[i];
    }
}

Seven::Seven(Seven &&other) noexcept : _size(other._size), _array(other._array) {
    other._size = 0;
    other._array = nullptr;
}

Seven::~Seven() noexcept {
    clean();
}

// --- Методы ---
void Seven::print() const {
    for (size_t i = 0; i < _size; ++i) {
        std::cout << static_cast<int>(_array[_size - 1 - i]); // Обратный порядок
    }
    std::cout << std::endl;
}

size_t Seven::size() const {
    return _size;
}

// --- Арифметические операции ---
Seven Seven::operator+(const Seven &other) const {
    size_t maxSize = std::max(_size, other._size);
    Seven result(maxSize + 1, 0); // Результат с запасом на перенос

    unsigned char carry = 0;
    for (size_t i = 0; i < maxSize; ++i) {
        unsigned char digit1 = i < _size ? _array[i] : 0;
        unsigned char digit2 = i < other._size ? other._array[i] : 0;
        unsigned char sum = digit1 + digit2 + carry;
        result._array[i] = sum % 7;
        carry = sum / 7;
    }
    if (carry) result._array[maxSize] = carry;

    // Удаление ведущих нулей
    if (result._array[maxSize] == 0) {
        --result._size;
    }

    return result;
}

Seven Seven::operator-(const Seven &other) const {
    if (*this < other) throw std::invalid_argument("Result cannot be negative.");

    Seven result(_size, 0);
    unsigned char borrow = 0;

    for (size_t i = 0; i < _size; ++i) {
        unsigned char digit1 = _array[i];
        unsigned char digit2 = i < other._size ? other._array[i] : 0;

        if (digit1 < digit2 + borrow) {
            result._array[i] = digit1 + 7 - digit2 - borrow;
            borrow = 1;
        } else {
            result._array[i] = digit1 - digit2 - borrow;
            borrow = 0;
        }
    }

    // Удаление ведущих нулей
    while (result._size > 1 && result._array[result._size - 1] == 0) {
        --result._size;
    }

    return result;
}

Seven& Seven::operator+=(const Seven &other) {
    *this = *this + other;
    return *this;
}

Seven& Seven::operator-=(const Seven &other) {
    *this = *this - other;
    return *this;
}

// --- Операции сравнения ---
bool Seven::operator==(const Seven &other) const {
    if (_size != other._size) return false;
    for (size_t i = 0; i < _size; ++i) {
        if (_array[i] != other._array[i]) return false;
    }
    return true;
}

bool Seven::operator!=(const Seven &other) const {
    return !(*this == other);
}

bool Seven::operator<(const Seven &other) const {
    if (_size != other._size) return _size < other._size;
    for (size_t i = _size; i-- > 0;) {
        if (_array[i] != other._array[i]) return _array[i] < other._array[i];
    }
    return false;
}

bool Seven::operator>(const Seven &other) const {
    return other < *this;
}

bool Seven::operator<=(const Seven &other) const {
    return !(other < *this);
}

bool Seven::operator>=(const Seven &other) const {
    return !(*this < other);
}

// --- Операторы присваивания ---
Seven& Seven::operator=(const Seven &other) {
    if (this == &other) return *this;

    clean();
_size = other._size;
    _array = new unsigned char[_size];
    for (size_t i = 0; i < _size; ++i) {
        _array[i] = other._array[i];
    }
    return *this;
}

Seven& Seven::operator=(Seven &&other) noexcept {
    if (this == &other) return *this;

    clean();
    _size = other._size;
    _array = other._array;
    other._size = 0;
    other._array = nullptr;
    return *this;
}

// --- Приватные методы ---
void Seven::validateSevenNumber(const std::string &t) {
    for (char c : t) {
        if (c < '0' || c > '6') {
            throw std::invalid_argument("Invalid digit in seven-based number.");
        }
    }
}

void Seven::clean() {
    delete[] _array;
    _array = nullptr;
    _size = 0;
}
