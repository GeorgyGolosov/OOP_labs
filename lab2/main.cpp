#include "include/seven.h"

int main() {
    try {
        // Создание объектов
        Seven a("1234");          // Семеричное число 1234 (в десятичной системе: 1 * 343 + 2 * 49 + 3 * 7 + 4 = 466)
        Seven b("56");            // Семеричное число 56 (в десятичной системе: 5 * 7 + 6 = 41)
        Seven c({1, 2, 3});       // Семеричное число 321 (в десятичной системе: 3 * 49 + 2 * 7 + 1 = 162)
        Seven d(5, 6);            // Семеричное число 66666 (в десятичной системе: 6 * (2401 + 343 + 49 + 7 + 1) = 14406)

        // Печать исходных чисел
        std::cout << "a = "; a.print();
        std::cout << "b = "; b.print();
        std::cout << "c = "; c.print();
        std::cout << "d = "; d.print();

        // Сложение
        Seven sum = a + b;
        std::cout << "\nSum (a + b) = "; sum.print();

        // Вычитание
        Seven diff = a - b;
        std::cout << "Difference (a - b) = "; diff.print();

        // Сложение с присваиванием
        a += b;
        std::cout << "a after (a += b): "; a.print();

        // Вычитание с присваиванием
        a -= b;
        std::cout << "a after (a -= b): "; a.print();

        // Сравнение чисел
        if (a == b) {
            std::cout << "a is equal to b\n";
        } else if (a > b) {
            std::cout << "a is greater than b\n";
        } else {
            std::cout << "a is less than b\n";
        }

        // Пример использования конструктора перемещения
        Seven temp("123");
        Seven moved = std::move(temp); // Перемещение
        std::cout << "\nMoved object: "; moved.print();

        // Ошибка: вычитание большего числа из меньшего
        try {
            Seven invalid = b - a;
            invalid.print();
        } catch (const std::exception &e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }

    } catch (const std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
