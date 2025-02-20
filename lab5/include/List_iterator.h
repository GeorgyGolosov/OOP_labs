#pragma once
#include <CustomMemoryResource.h>

template <class ItemT, class Node>
class ListIterator {
private:
    Node* current;

public:
    // Конструктор принимает указатель на узел
    explicit ListIterator(Node* node) : current(node) {}

    // Префиксный инкремент: переходит к следующему узлу
    ListIterator<ItemT, Node>& operator++() {
        if (current != nullptr)
            current = current->next;
        return *this;
    }

    // Постфиксный инкремент
    ListIterator<ItemT, Node> operator++(int) {
        ListIterator<ItemT, Node> temp(*this);
        if (current != nullptr)
            current = current->next;
        return temp;
    }

    // Операторы сравнения
    bool operator==(const ListIterator<ItemT, Node>& other) const {
        return current == other.current;
    }

    bool operator!=(const ListIterator<ItemT, Node>& other) const {
        return current != other.current;
    }

    // Оператор разыменования возвращает ссылку на данные узла
    ItemT& operator*() const {
        if (current == nullptr)
            throw std::exception();
        return current->data;
    }

    // Оператор -> возвращает указатель на данные узла
    ItemT* operator->() const {
        if (current == nullptr)
            throw std::exception();
        return &(current->data);
    }
};
