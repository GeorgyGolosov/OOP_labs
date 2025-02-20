#include "../include/List.h"
#include "../include/CustomMemoryResource.h"
#include <iostream>

// Определение структуры AB
struct AB {
    int a;
    int b;
};

int main()
{
    CustomMemoryResource customResource(500);

    // Создаем аллокаторы для разных типов данных
    std::pmr::polymorphic_allocator<int> allocator1(&customResource);
    std::pmr::polymorphic_allocator<char> allocator2(&customResource);
    std::pmr::polymorphic_allocator<AB> allocator3(&customResource);

    // Создаем списки для разных типов данных
    List<int, std::pmr::polymorphic_allocator<int>> list1(allocator1);
    List<char, std::pmr::polymorphic_allocator<char>> list2(allocator2);
    List<AB, std::pmr::polymorphic_allocator<AB>> list3(allocator3);

    // Добавляем элементы в списки
    list1.push_front(10);
    list1.push_front(20);

    list2.push_front('a');
    list2.push_front('b');

    list3.push_front({101, 202});
    list3.push_front({303, 404});

    // Выводим содержимое списков через итераторы
    std::cout << "List1:\n";
    for (auto it = list1.begin(); it != list1.end(); ++it)
    {
        std::cout << *it << '\n';
    }

    std::cout << "List2:\n";
    for (auto it = list2.begin(); it != list2.end(); ++it)
    {
        std::cout << *it << '\n';
    }

    std::cout << "List3:\n";
    for (auto it = list3.begin(); it != list3.end(); ++it)
    {
        std::cout << it->a << ' ' << it->b << '\n';
    }

    std::cout << "End!\n";
    return 0;
}
