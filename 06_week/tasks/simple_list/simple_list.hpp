#pragma once

#include <memory>
#include <string>

class SimpleList {
private:
    struct Node {
        std::string value;
        std::shared_ptr<Node> next{nullptr};
        std::weak_ptr<Node> prev;

        explicit Node(const std::string& val);
        explicit Node(std::string&& val);
    };

    std::shared_ptr<Node> head_{nullptr};
    std::weak_ptr<Node> tail_;
    size_t size_ = 0;

public:
    SimpleList() = default;
    SimpleList(const SimpleList& other);
    SimpleList& operator=(const SimpleList& other);
    SimpleList(SimpleList&& other) noexcept;
    SimpleList& operator=(SimpleList&& other) noexcept;
    ~SimpleList() = default;

    void Swap(SimpleList& other) noexcept;
    size_t Size() const noexcept;
    bool Empty() const noexcept;
    void PushBack(const std::string& value);
    void PushBack(std::string&& value);
    void PopBack();
    void PushFront(const std::string& value);
    void PushFront(std::string&& value);
    void PopFront();
    std::string& Back();
    const std::string& Back() const;
    std::string& Front();
    const std::string& Front() const;
    void Clear();
};

void Swap(SimpleList& a, SimpleList& b) noexcept;
