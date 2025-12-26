#include "queue.hpp"

void Queue::TransferIfNeeded() const {
    if (output_stack_.empty() && input_stack_.empty() == false) {
        while (input_stack_.empty() == false) {
            output_stack_.push_back(input_stack_.back());
            input_stack_.pop_back();
        }
    }
}

Queue::Queue(size_t capacity) {
    input_stack_.reserve(capacity);
}

Queue::Queue(const std::vector<int>& vec) {
    input_stack_ = vec;
}

Queue::Queue(std::stack<int> s) {
    std::vector<int> temp;
    temp.reserve(s.size());
    while (s.empty() == false) {
        temp.push_back(s.top());
        s.pop();
    }
    std::reverse(temp.begin(), temp.end());
    input_stack_ = std::move(temp);
}

Queue::Queue(std::initializer_list<int> init) {
    input_stack_.assign(init.begin(), init.end());
}

void Queue::Push(int value) {
    input_stack_.push_back(value);
}

bool Queue::Pop() {
    TransferIfNeeded();
    if (output_stack_.empty()) {
        return false;
    }
    output_stack_.pop_back();
    return true;
}

int& Queue::Front() {
    TransferIfNeeded();
    if (output_stack_.empty()) {
        return dummy_;
    }
    return output_stack_.back();
}

const int& Queue::Front() const {
    TransferIfNeeded();
    if (output_stack_.empty()) {
        return dummy_;
    }
    return output_stack_.back();
}

int& Queue::Back() {
    if (input_stack_.empty() == false) {
        return input_stack_.back();
    }
    if (output_stack_.empty() == false) {
        return output_stack_.front();
    }
    return dummy_;
}

const int& Queue::Back() const {
    if (input_stack_.empty() == false) {
        return input_stack_.back();
    }
    if (output_stack_.empty() == false) {
        return output_stack_.front();
    }
    return dummy_;
}

bool Queue::Empty() const {
    return input_stack_.empty() && output_stack_.empty();
}

size_t Queue::Size() const {
    return input_stack_.size() + output_stack_.size();
}

void Queue::Clear() {
    input_stack_.clear();
    output_stack_.clear();
}

void Queue::Swap(Queue& other) {
    input_stack_.swap(other.input_stack_);
    output_stack_.swap(other.output_stack_);
}

bool Queue::operator==(const Queue& other) const {
    if (Size() != other.Size()) {
        return false;
    }

    Queue a = *this;
    Queue b = other;

    while (a.Empty() == false) {
        if (a.Front() != b.Front()) {
            return false;
        }
        a.Pop();
        b.Pop();
    }
    return true;
}

bool Queue::operator!=(const Queue& other) const {
    return (*this == other) == false;
}