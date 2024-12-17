#include <gtest/gtest.h>
#include "../include/seven.h"


// Тесты на конструкторы

TEST(SevenTest, DefaultConstructor) {
    Seven s;
    std::ostringstream os;
    s.print(os);
    ASSERT_EQ(os.str(), "");  // Пустой объект
}

TEST(SevenTest, SizeValueConstructor) {
    Seven s(3, 1);  // 3 цифры, все равны 1
    std::ostringstream os;
    s.print(os);
    ASSERT_EQ(os.str(), "111");  // Ожидаем "111"
}

TEST(SevenTest, StringConstructor) {
    Seven s("123");  // Строка, представляющая число 123
    std::ostringstream os;
    s.print(os);
    ASSERT_EQ(os.str(), "123");  // Ожидаем "123"
}

TEST(SevenTest, InvalidStringConstructor) {
    bool exceptionCaught = false;
    try {
        Seven s("1238");  // Некорректная строка (цифра 8 не является семеричной)
    } catch (const std::invalid_argument& e) {
        exceptionCaught = true;
    }
    ASSERT_TRUE(exceptionCaught);  // Ожидаем выброс исключения
}

// Тесты на операторы сложения и вычитания

TEST(SevenTest, Addition) {
    Seven a("111");
    Seven b("111");
    Seven result = a + b;
    std::ostringstream os;
    result.print(os);
    ASSERT_EQ(os.str(), "222");
}

TEST(SevenTest, AdditionWithCarry) {
    Seven a("666");
    Seven b("111");
    Seven result = a + b;
    std::ostringstream os;
    result.print(os);
    ASSERT_EQ(os.str(), "1110");  // Ожидаемый результат с увеличением порядка числа
}

TEST(SevenTest, Subtraction) {
    Seven a("666");
    Seven b("111");
    Seven result = a - b;
    std::ostringstream os;
    result.print(os);
    ASSERT_EQ(os.str(), "555");
}

TEST(SevenTest, SubtractionWithBorrow) {
    Seven a("1000");
    Seven b("666");
    Seven result = a - b;
    std::ostringstream os;
    result.print(os);
    ASSERT_EQ(os.str(), "1");  // Ожидаемый результат с заёмом
}

TEST(SevenTest, SubtractionNegativeResult) {
    bool exceptionCaught = false;
    try {
        Seven a("100");
        Seven b("200");
        Seven result = a - b;  // Попытка вычитания из большего числа меньшее
    } catch (const std::invalid_argument& e) {
        exceptionCaught = true;
    }
    ASSERT_TRUE(exceptionCaught);
}

// Операторы сравнения
TEST(SevenTest, EqualityOperator) {
    Seven a("123");
    Seven b("123");
    ASSERT_TRUE(a == b);
}

TEST(SevenTest, NotEqualOperator) {
    Seven a("123");
    Seven b("456");
    ASSERT_FALSE(a == b);
}

TEST(SevenTest, LessThanOperator) {
    Seven a("123");
    Seven b("456");
    ASSERT_TRUE(a < b);
}

TEST(SevenTest, GreaterThanOperator) {
    Seven a("611");
    Seven b("456");
    ASSERT_TRUE(a > b);
}

// Тест на присваивание и перемещение

TEST(SevenTest, CopyAssignment) {
    Seven a("123");
    Seven b("456");
    b = a;  // Присваивание
    std::ostringstream os;
    b.print(os);
    ASSERT_EQ(os.str(), "123");
}

TEST(SevenTest, MoveAssignment) {
    Seven a("123");
    Seven b("456");
    b = std::move(a);  // Перемещение
    std::ostringstream os;
    b.print(os);
    ASSERT_EQ(os.str(), "123");
}

// Тесты на конструкторы копирования и перемещения

TEST(SevenTest, CopyConstructor) {
    Seven a("123");
    Seven b(a);  // Конструктор копирования
    std::ostringstream os;
    b.print(os);
    ASSERT_EQ(os.str(), "123");  // Ожидаем, что объект b будет равен "123"
}

TEST(SevenTest, MoveConstructor) {
    Seven a("123");
    Seven b(std::move(a));  // Конструктор перемещения
    std::ostringstream os;
    b.print(os);
    ASSERT_EQ(os.str(), "123");  // Ожидаем, что объект b будет равен "123"
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
