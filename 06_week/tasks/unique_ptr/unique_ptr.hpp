#pragma once

#include <string>

class UniquePtr {
private:
    std::string* ptr_{nullptr};

public:
    UniquePtr();
    explicit UniquePtr(std::string* ptr);
    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;
    UniquePtr(UniquePtr&& other) noexcept;
    UniquePtr& operator=(UniquePtr&& other) noexcept;
    ~UniquePtr();

    std::string& operator*() const;
    std::string* operator->() const;
    explicit operator bool() const;

    std::string* Get() const;
    std::string* Release();
    void Reset(std::string* ptr = nullptr);
    void Swap(UniquePtr& other) noexcept;
};

UniquePtr MakeUnique(std::string str);
void Swap(UniquePtr& a, UniquePtr& b) noexcept;
