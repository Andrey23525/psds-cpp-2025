#pragma once

#include <string>
#include <utility>

struct ControlBlock {
    std::string* ptr{nullptr};
    size_t shared_cnt{0};
    size_t weak_cnt{0};

    explicit ControlBlock(std::string* p);
};

class WeakPtr;

class SharedPtr {
private:
    void Release();

    ControlBlock* cb_{nullptr};

public:
    SharedPtr();
    explicit SharedPtr(std::string* p);
    SharedPtr(const SharedPtr& other);
    SharedPtr& operator=(const SharedPtr& other);
    SharedPtr(SharedPtr&& other) noexcept;
    SharedPtr& operator=(SharedPtr&& other) noexcept;
    explicit SharedPtr(ControlBlock* cb);
    ~SharedPtr();

    explicit operator bool() const;
    std::string& operator*() const;
    std::string* operator->() const;

    std::string* Get() const;
    void Reset(std::string* p = nullptr);
    void Swap(SharedPtr& other) noexcept;
    size_t UseCount() const;
    ControlBlock* GetControlBlock() const;
};

class WeakPtr {
private:
    void Release();

    ControlBlock* cb_{nullptr};

public:
    WeakPtr();
    explicit WeakPtr(const SharedPtr& sp);
    WeakPtr(const WeakPtr& other);
    WeakPtr& operator=(const WeakPtr& other);
    WeakPtr(WeakPtr&& other) noexcept;
    WeakPtr& operator=(WeakPtr&& other) noexcept;
    ~WeakPtr();

    WeakPtr& operator=(const SharedPtr& sp);

    void Reset();
    void Swap(WeakPtr& other) noexcept;
    size_t UseCount() const;
    bool Expired() const;
    SharedPtr Lock() const;
};

template <typename T>
SharedPtr MakeShared(T&& value) {
    return SharedPtr(new std::string(std::forward<T>(value)));
}

void Swap(SharedPtr& a, SharedPtr& b) noexcept;
void Swap(WeakPtr& a, WeakPtr& b) noexcept;
