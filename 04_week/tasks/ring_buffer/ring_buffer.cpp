#include "ring_buffer.hpp"
#include <algorithm>

size_t RingBuffer::CalculateIndex(size_t logical_index) const {
    return (tail_ + logical_index) % capacity_;
}

RingBuffer::RingBuffer(size_t capacity)
    : capacity_(capacity == 0 ? 1 : capacity)
    , size_(0)
    , head_(0)
    , tail_(0) {
    data_.resize(capacity_);
}

RingBuffer::RingBuffer(size_t capacity, int value)
    : capacity_(capacity == 0 ? 1 : capacity)
    , size_(capacity_)
    , head_(0)
    , tail_(0) {
    data_.resize(capacity_, value);
}

RingBuffer::RingBuffer(std::initializer_list<int> init)
    : capacity_(init.size() == 0 ? 1 : init.size())
    , size_(init.size())
    , head_(0)
    , tail_(0) {
    data_.resize(capacity_);
    size_t idx = 0;
    for (int value : init) {
        data_[idx++] = value;
    }
}

RingBuffer::RingBuffer(const RingBuffer& other)
    : data_(other.data_)
    , capacity_(other.capacity_)
    , size_(other.size_)
    , head_(other.head_)
    , tail_(other.tail_) {
}

RingBuffer& RingBuffer::operator=(const RingBuffer& other) {
    if (this != &other) {
        data_ = other.data_;
        capacity_ = other.capacity_;
        size_ = other.size_;
        head_ = other.head_;
        tail_ = other.tail_;
    }
    return *this;
}

void RingBuffer::Push(int value) {
    data_[head_] = value;
    head_ = (head_ + 1) % capacity_;

    if (size_ < capacity_) {
        ++size_;
    } else {
        tail_ = (tail_ + 1) % capacity_;
    }
}

bool RingBuffer::TryPush(int value) {
    if (Full()) {
        return false;
    }
    Push(value);
    return true;
}

void RingBuffer::Pop() {
    if (Empty()) {
        return;
    }
    tail_ = (tail_ + 1) % capacity_;
    --size_;
}

bool RingBuffer::TryPop(int& value) {
    if (Empty()) {
        return false;
    }
    value = data_[tail_];
    Pop();
    return true;
}

int& RingBuffer::operator[](size_t index) {
    return data_[CalculateIndex(index)];
}

const int& RingBuffer::operator[](size_t index) const {
    return data_[CalculateIndex(index)];
}

int& RingBuffer::Front() {
    size_t front_idx = (head_ + capacity_ - 1) % capacity_;
    return data_[front_idx];
}

const int& RingBuffer::Front() const {
    size_t front_idx = (head_ + capacity_ - 1) % capacity_;
    return data_[front_idx];
}

int& RingBuffer::Back() {
    return data_[tail_];
}

const int& RingBuffer::Back() const {
    return data_[tail_];
}

bool RingBuffer::Empty() const {
    return size_ == 0;
}

bool RingBuffer::Full() const {
    return size_ == capacity_;
}

size_t RingBuffer::Size() const {
    return size_;
}

size_t RingBuffer::Capacity() const {
    return capacity_;
}

void RingBuffer::Clear() {
    size_ = 0;
    head_ = 0;
    tail_ = 0;
}

void RingBuffer::Resize(size_t new_capacity) {
    if (new_capacity == 0) {
        new_capacity = 1;
    }

    if (new_capacity == capacity_) {
        return;
    }

    std::vector<int> new_data(new_capacity);
    size_t new_size = std::min(size_, new_capacity);

    size_t start_offset = 0;
    if (size_ > new_capacity) {
        start_offset = size_ - new_capacity;
    }

    for (size_t i = 0; i < new_size; ++i) {
        new_data[i] = data_[CalculateIndex(start_offset + i)];
    }

    data_ = std::move(new_data);
    capacity_ = new_capacity;
    size_ = new_size;
    tail_ = 0;
    head_ = new_size % capacity_;
}

std::vector<int> RingBuffer::Vector() const {
    std::vector<int> result;
    result.reserve(size_);

    for (size_t i = 0; i < size_; ++i) {
        result.push_back(data_[CalculateIndex(i)]);
    }

    return result;
}