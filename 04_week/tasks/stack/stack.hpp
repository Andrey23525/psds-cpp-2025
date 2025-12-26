#pragma once

#include <vector>

class Stack {
private:
    std::vector<int> data_;

public:
    void Push(int value);

    // Возвращает true если операция выполнена, false если стек пуст
    bool Pop();

    int& Top();
    const int& Top() const;

    bool Empty() const;
    size_t Size() const;
    void Clear();
    void Swap(Stack& other);

    bool operator==(const Stack& other) const;
    bool operator!=(const Stack& other) const;
};