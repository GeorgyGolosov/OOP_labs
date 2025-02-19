#pragma once
#include <memory>
#include <stdexcept>
#include <utility>

template<typename T>
class Array {
private:
    std::shared_ptr<T[]> data;
    size_t _size;
    size_t _capacity;
public:
    Array(size_t capacity) : _size(0), _capacity(capacity) {
         data = std::shared_ptr<T[]>(new T[capacity], std::default_delete<T[]>());
    }
    Array() : _size(0), _capacity(1) {
         data = std::shared_ptr<T[]>(new T[1], std::default_delete<T[]>());
    }
    size_t size() const { return _size; }
    size_t capacity() const { return _capacity; }

    T& operator[](size_t index) {
         if(index >= _size) throw std::out_of_range("Index out of range");
         return data[index];
    }

    const T& operator[](size_t index) const {
         if(index >= _size) throw std::out_of_range("Index out of range");
         return data[index];
    }

    void push_back(const T& element) {
         if(_size == _capacity) {
             resize(_capacity * 2);
         }
         data[_size++] = element;
    }

    void push_back(T&& element) {
         if(_size == _capacity) {
             resize(_capacity * 2);
         }
         data[_size++] = std::move(element);
    }

    void remove(size_t index) {
         if(index >= _size) throw std::out_of_range("Index out of range");
         for(size_t i = index; i < _size - 1; i++){
             data[i] = std::move(data[i+1]);
         }
         _size--;
    }

private:
    void resize(size_t new_capacity) {
         std::shared_ptr<T[]> new_data(new T[new_capacity], std::default_delete<T[]>());
         for(size_t i = 0; i < _size; i++){
             new_data[i] = std::move(data[i]);
         }
         data = new_data;
         _capacity = new_capacity;
    }
};
