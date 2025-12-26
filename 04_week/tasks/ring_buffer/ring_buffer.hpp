#pragma once

#include <vector>
#include <initializer_list>

class RingBuffer {
private:
    std::vector<int> data_;
    size_t capacity_ = 0;
    size_t size_ = 0;
    size_t head_ = 0;  // индекс для добавления (Front)
    size_t tail_ = 0;  // индекс для удаления (Back)

    // Метод для получения индекса
    size_t CalculateIndex(size_t logical_index) const;

public:
    explicit RingBuffer(size_t capacity);
    RingBuffer(size_t capacity, int value);
    RingBuffer(std::initializer_list<int> init);
    RingBuffer(const RingBuffer& other);

    void Push(int value);
    bool TryPush(int value);

    void Pop();
    bool TryPop(int& value);

    int& Front();
    const int& Front() const;

    int& Back();
    const int& Back() const;

    bool Empty() const;
    bool Full() const;
    size_t Size() const;
    size_t Capacity() const;
    void Clear();
    void Resize(size_t new_capacity);
    std::vector<int> Vector() const;

    int& operator[](size_t index);
    const int& operator[](size_t index) const;
    RingBuffer& operator=(const RingBuffer& other);

};