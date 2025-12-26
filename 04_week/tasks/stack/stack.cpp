#include "stack.hpp"

void Stack::Push(int value) {
    data_.push_back(value);
}

bool Stack::Pop() {
    if (data_.empty()) {
        return false;
    }
    data_.pop_back();
    return true;
}

int& Stack::Top() {
    if (data_.empty()) {
        static int dummy = 0;
        return dummy;
    }
    return data_.back();
}

const int& Stack::Top() const {
    if (data_.empty()) {
        static constexpr int dummy = 0;
        return dummy;
    }
    return data_.back();
}

bool Stack::Empty() const {
    return data_.empty();
}

size_t Stack::Size() const {
    return data_.size();
}

void Stack::Clear() {
    data_.clear();
}

void Stack::Swap(Stack& other) {
    data_.swap(other.data_);
}

bool Stack::operator==(const Stack& other) const {
    return data_ == other.data_;
}

bool Stack::operator!=(const Stack& other) const {
    return data_ != other.data_;
}