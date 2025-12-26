#pragma once

#include <algorithm>
#include <vector>
#include <stack>
#include <initializer_list>
#include <cstddef>

class Queue {
private:
    mutable std::vector<int> input_stack_;
    mutable std::vector<int> output_stack_;
    mutable int dummy_ = 0;

    void TransferIfNeeded() const;

public:
    Queue() = default;

    explicit Queue(size_t capacity);
    explicit Queue(const std::vector<int>& vec);
    explicit Queue(std::stack<int> s);
    Queue(std::initializer_list<int> init);

    void Push(int value);
    bool Pop();
    int& Front();
    const int& Front() const;
    int& Back();
    const int& Back() const;
    bool Empty() const;
    size_t Size() const;
    void Clear();
    void Swap(Queue& other);

    bool operator==(const Queue& other) const;
    bool operator!=(const Queue& other) const;
};