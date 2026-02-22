#include "simple_list.hpp"

SimpleList::Node::Node(const std::string& val) : value(val) {}

SimpleList::Node::Node(std::string&& val) : value(std::move(val)) {}

SimpleList::SimpleList(const SimpleList& other) {
    for (auto it = other.head_; it; it = it->next) {
        PushBack(it->value);
    }
}

SimpleList::SimpleList(SimpleList&& other) noexcept {
    Swap(other);
    other.Clear();
}

SimpleList& SimpleList::operator=(const SimpleList& other) {
    if (this != &other) {
        SimpleList tmp(other);
        Swap(tmp);
    }

    return *this;
}

SimpleList& SimpleList::operator=(SimpleList&& other) noexcept {
    if (this != &other) {
        Clear();
        Swap(other);
    }

    return *this;
}

void SimpleList::Swap(SimpleList& other) noexcept {
    std::swap(head_, other.head_);
    std::swap(tail_, other.tail_);
    std::swap(size_, other.size_);
}

void Swap(SimpleList& a, SimpleList& b) noexcept {
    a.Swap(b);
}

size_t SimpleList::Size() const noexcept {
    return size_;
}

bool SimpleList::Empty() const noexcept {
    return size_ == 0;
}

std::string& SimpleList::Front() {
    return head_->value;
}

const std::string& SimpleList::Front() const {
    return head_->value;
}

std::string& SimpleList::Back() {
    return tail_.lock()->value;
}

const std::string& SimpleList::Back() const {
    return tail_.lock()->value;
}

void SimpleList::PushBack(const std::string& value) {
    PushBack(std::string(value));
}

void SimpleList::PushBack(std::string&& value) {
    const auto node = std::make_shared<Node>(std::move(value));

    if (head_) {
        const auto tail = tail_.lock();
        node->prev = tail;
        tail->next = node;
    } else {
        head_ = node;
    }

    tail_ = node;
    ++size_;
}

void SimpleList::PushFront(const std::string& value) {
    PushFront(std::string(value));
}

void SimpleList::PushFront(std::string&& value) {
    const auto node = std::make_shared<Node>(std::move(value));

    if (head_) {
        node->next = head_;
        head_->prev = node;
    } else {
        tail_ = node;
    }

    head_ = node;
    ++size_;
}

void SimpleList::PopBack() {
    if (!head_) {
        return;
    }

    const auto tail = tail_.lock();
    const auto prev = tail->prev.lock();

    if (prev) {
        prev->next = nullptr;
        tail_ = prev;
    } else {
        head_ = nullptr;
        tail_ = {};
    }

    --size_;
}

void SimpleList::PopFront() {
    if (!head_) {
        return;
    }

    if (head_->next) {
        head_->next->prev = {};
        head_ = head_->next;
    } else {
        head_ = nullptr;
        tail_ = {};
    }

    --size_;
}

void SimpleList::Clear() {
    while (head_) {
        head_ = std::move(head_->next);
    }

    tail_ = {};
    size_ = 0;
}
