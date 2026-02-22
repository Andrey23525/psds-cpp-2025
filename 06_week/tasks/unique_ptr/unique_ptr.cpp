#include "unique_ptr.hpp"

UniquePtr::UniquePtr() = default;

UniquePtr::UniquePtr(std::string* ptr) : ptr_(ptr) {}

UniquePtr::UniquePtr(UniquePtr&& other) noexcept : ptr_(other.ptr_) {
    other.ptr_ = nullptr;
}

UniquePtr& UniquePtr::operator=(UniquePtr&& other) noexcept {
    if (this != &other) {
        delete ptr_;
        ptr_ = other.ptr_;

        other.ptr_ = nullptr;
    }

    return *this;
}

UniquePtr::~UniquePtr() {
    delete ptr_;
}

std::string& UniquePtr::operator*() const {
    return *ptr_;
}

std::string* UniquePtr::operator->() const {
    return ptr_;
}

UniquePtr::operator bool() const {
    return ptr_ != nullptr;
}

std::string* UniquePtr::Get() const {
    return ptr_;
}

std::string* UniquePtr::Release() {
    std::string* tmp = ptr_;
    ptr_ = nullptr;

    return tmp;
}

void UniquePtr::Reset(std::string* ptr) {
    delete ptr_;
    ptr_ = ptr;
}

void UniquePtr::Swap(UniquePtr& other) noexcept {
    std::swap(ptr_, other.ptr_);
}

UniquePtr MakeUnique(std::string str) {
    return UniquePtr(new std::string(std::move(str)));
}

void Swap(UniquePtr& a, UniquePtr& b) noexcept {
    a.Swap(b);
}
