#include "include/seven.h"

int main()
{
    std::cout << std::boolalpha;
    std::string num1, num2;
    char op;

    // Ввод данных
    std::cout << "Введите первое число (в семеричной системе): ";
    std::cin >> num1;
    std::cout << "Введите второе число (в семеричной системе): ";
    std::cin >> num2;
    std::cout << "Введите операцию из [+,-,>,<,==]: ";
    std::cin >> op;

    Seven first(num1), second(num2);

    std::cout << "\nОтвет: ";
    switch (op) {
    case '+': {
        Seven sum = first + second;
        sum.print(std::cout);
        break;
    }
    case '-': {
        Seven diff = first - second;
        diff.print(std::cout);
        break;
    }
    case '=': {
        std::cout << (first == second);
        break;
    }
    case '<': {
        std::cout << (first < second);
        break;
    }
    case '>': {
        std::cout << (first > second);
        break;
    }
    default: {
        std::cerr << "Ошибка: недопустимая операция.\n";
        break;
    }
    }

    std::cout << '\n';
    return 0;
}
