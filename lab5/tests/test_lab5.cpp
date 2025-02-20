#include <gtest/gtest.h>
#include "../include/CustomMemoryResource.h"
#include "../include/List.h"

// Вспомогательная функция для подсчёта количества элементов в списке.
template <typename T, typename Allocator>
size_t list_size(const List<T, Allocator>& list) {
    size_t count = 0;
    for (auto it = list.begin(); it != list.end(); ++it)
        ++count;
    return count;
}

// Вспомогательная функция для сравнения двух списков.
template <typename T, typename Allocator>
bool list_equal(const List<T, Allocator>& a, const List<T, Allocator>& b) {
    auto itA = a.begin();
    auto itB = b.begin();
    while (itA != a.end() && itB != b.end()) {
        if (*itA != *itB)
            return false;
        ++itA;
        ++itB;
    }
    return (itA == a.end() && itB == b.end());
}

TEST(test_01, basic_test_set) {
    CustomMemoryResource customResource(500);
    std::pmr::polymorphic_allocator<int> allocator(&customResource);
    List<int, std::pmr::polymorphic_allocator<int>> list(allocator);

    list.push_front(30);
    list.push_front(20);
    list.push_front(10);

    ASSERT_EQ(list_size(list), 3);
}

TEST(test_02, basic_test_set) {
    CustomMemoryResource customResource(500);
    std::pmr::polymorphic_allocator<int> allocator(&customResource);
    List<int, std::pmr::polymorphic_allocator<int>> list(allocator);

    list.push_front(30);
    list.push_front(20);
    list.push_front(10);

    list.pop_front();  // удаляем первый элемент (последний добавленный)
    ASSERT_EQ(list_size(list), 2);
}

TEST(test_03, basic_test_set) {
    CustomMemoryResource customResource(500);
    std::pmr::polymorphic_allocator<int> allocator(&customResource);
    List<int, std::pmr::polymorphic_allocator<int>> list(allocator);

    list.push_front(30);
    list.push_front(20);
    list.push_front(10);

    list.pop_front();
    list.pop_front();
    list.pop_front();

    ASSERT_TRUE(list.empty());
}

TEST(test_04, basic_test_set) {
    CustomMemoryResource customResource(500);
    std::pmr::polymorphic_allocator<int> allocator(&customResource);
    List<int, std::pmr::polymorphic_allocator<int>> list1(allocator);
    List<int, std::pmr::polymorphic_allocator<int>> list2(allocator);

    list1.push_front(20);
    list1.push_front(10);

    list2.push_front(20);
    list2.push_front(10);

    ASSERT_TRUE(list_equal(list1, list2));
}

TEST(test_05, basic_test_set) {
    CustomMemoryResource customResource(500);
    std::pmr::polymorphic_allocator<int> allocator(&customResource);
    List<int, std::pmr::polymorphic_allocator<int>> list1(allocator);
    List<int, std::pmr::polymorphic_allocator<int>> list2(allocator);

    list1.push_front(20);
    list1.push_front(10);

    list2.push_front(20);
    list2.push_front(10);

    ASSERT_EQ(*list1.begin(), *list2.begin());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
