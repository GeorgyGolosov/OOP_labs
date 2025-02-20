#pragma once
#include <iostream>
#include <memory_resource>
#include <vector>
#include <memory>
#include <algorithm>
#include <exception>

class CustomMemoryResource : public std::pmr::memory_resource {
private:
    struct Block {
        size_t offset{0};
        size_t size{0};
        Block(size_t off, size_t sz) : offset(off), size(sz) {}
    };

    char* buffer;
    std::vector<Block> used_blocks;
    size_t max_size;

public:
    explicit CustomMemoryResource(size_t capacity) noexcept {
        buffer = new char[capacity];
        max_size = capacity;
    }

    ~CustomMemoryResource() override {
        delete[] buffer;
    }

protected:
    void* do_allocate(size_t bytes, size_t alignment) override {
        if (bytes == 0)
            return nullptr;

        size_t result = 0;
        // Поиск свободного участка с учётом уже выделенных блоков
        for (const Block &b : used_blocks)
            if ((result + bytes > b.offset) && (result < b.offset + b.size))
                result = b.offset + b.size;

        if (result + bytes >= max_size)
            throw std::bad_alloc();

        used_blocks.emplace_back(result, bytes);
        std::sort(used_blocks.begin(), used_blocks.end(), [](const Block &lhs, const Block &rhs) {
            return lhs.offset < rhs.offset;
        });
        return buffer + result;
    }

    void do_deallocate(void* ptr, size_t bytes, size_t alignment) override {
        if (ptr == nullptr)
            return;

        size_t offset = static_cast<char*>(ptr) - buffer;
        for (size_t i = 0; i < used_blocks.size(); ++i) {
            if (used_blocks[i].offset == offset) {
                used_blocks.erase(used_blocks.begin() + i);
                return;
            }
        }
        throw std::logic_error("удаление не выделяемого блока");
    }

    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override {
        return this == &other;
    }
};
