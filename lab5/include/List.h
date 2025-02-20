#pragma once
#include <CustomMemoryResource.h>
#include "List_iterator.h"
#include <stdexcept>
#include <type_traits>
#include <memory>
#include <memory_resource>

template <class T, class allocator_type>
    requires std::is_default_constructible_v<T> && std::is_same_v<allocator_type, std::pmr::polymorphic_allocator<T>>
class List {
private:
    // Дружественный доступ для итератора
    template <class ItemT, class NodeT>
    friend class ListIterator;

    allocator_type allocator;

    // Внутренняя структура узла списка
    struct Node {
        T data;
        Node* next;
        Node(const T& d, Node* n) : data(d), next(n) {}
    };

    Node* head;

    // Создаем аллокатор для Node
    using NodeAllocator = std::pmr::polymorphic_allocator<Node>;
    NodeAllocator nodeAlloc;  // Объявляем поле для аллокатора узлов

public:
    // Конструктор, инициализирующий nodeAlloc через alloc.resource()
    List(allocator_type alloc = {}) noexcept
        : allocator(alloc), nodeAlloc(alloc.resource()), head(nullptr) {}

    // Деструктор – освобождает все узлы списка
    ~List() {
        while (head != nullptr) {
            Node* tmp = head;
            head = head->next;
            std::allocator_traits<NodeAllocator>::destroy(nodeAlloc, tmp);
            std::allocator_traits<NodeAllocator>::deallocate(nodeAlloc, tmp, 1);
        }
    }

    // Вставка элемента в начало списка
    void push_front(const T& value) noexcept {
        Node* newNode = std::allocator_traits<NodeAllocator>::allocate(nodeAlloc, 1);
        std::allocator_traits<NodeAllocator>::construct(nodeAlloc, newNode, Node(value, head));
        head = newNode;
    }

    // Удаление первого элемента списка с возвратом его значения
    T pop_front() {
        if (head == nullptr)
            throw std::exception();
        Node* nodeToRemove = head;
        T value = nodeToRemove->data;
        head = head->next;
        std::allocator_traits<NodeAllocator>::destroy(nodeAlloc, nodeToRemove);
        std::allocator_traits<NodeAllocator>::deallocate(nodeAlloc, nodeToRemove, 1);
        return value;
    }

    // Проверка на пустоту
    bool empty() const noexcept {
        return head == nullptr;
    }

    // Возвращает итератор на первый элемент списка
    ListIterator<T, Node> begin() noexcept {
        return ListIterator<T, Node>(head);
    }

    // Возвращает итератор, обозначающий конец списка
    ListIterator<T, Node> end() noexcept {
        return ListIterator<T, Node>(nullptr);
    }

    // Константные версии begin() и end()
    ListIterator<T, Node> begin() const noexcept {
        return ListIterator<T, Node>(head);
    }

    ListIterator<T, Node> end() const noexcept {
        return ListIterator<T, Node>(nullptr);
    }
};
