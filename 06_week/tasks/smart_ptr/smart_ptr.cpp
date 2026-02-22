#include "smart_ptr.hpp"

ControlBlock::ControlBlock(std::string* p) : ptr(p), shared_cnt(1) {}

SharedPtr::SharedPtr() = default;

SharedPtr::SharedPtr(std::string* p) : cb_(p ? new ControlBlock(p) : nullptr) {}

SharedPtr::SharedPtr(const SharedPtr& other) : cb_(other.cb_) {
    if (cb_) {
        ++cb_->shared_cnt;
    }
}

SharedPtr::SharedPtr(SharedPtr&& other) noexcept : cb_(other.cb_) {
    other.cb_ = nullptr;
}

SharedPtr::SharedPtr(ControlBlock* cb) : cb_(cb) {
    if (cb_) {
        ++cb_->shared_cnt;
    }
}

SharedPtr::~SharedPtr() {
    Release();
}

SharedPtr& SharedPtr::operator=(const SharedPtr& other) {
    if (this != &other) {
        Release();
        cb_ = other.cb_;

        if (cb_) {
            ++cb_->shared_cnt;
        }
    }

    return *this;
}

SharedPtr& SharedPtr::operator=(SharedPtr&& other) noexcept {
    if (this != &other) {
        Release();
        cb_ = other.cb_;

        other.cb_ = nullptr;
    }

    return *this;
}

std::string* SharedPtr::Get() const {
    return cb_ ? cb_->ptr : nullptr;
}

void SharedPtr::Reset(std::string* p) {
    Release();
    cb_ = p ? new ControlBlock(p) : nullptr;
}

void SharedPtr::Swap(SharedPtr& other) noexcept {
    std::swap(cb_, other.cb_);
}

size_t SharedPtr::UseCount() const {
    return cb_ ? cb_->shared_cnt : 0;
}

SharedPtr::operator bool() const {
    return cb_ && cb_->ptr != nullptr;
}

std::string& SharedPtr::operator*() const {
    return *cb_->ptr;
}

std::string* SharedPtr::operator->() const {
    return cb_->ptr;
}

ControlBlock* SharedPtr::GetControlBlock() const {
    return cb_;
}

void SharedPtr::Release() {
    if (!cb_) return;

    if (--cb_->shared_cnt == 0) {
        delete cb_->ptr;
        cb_->ptr = nullptr;

        if (cb_->weak_cnt == 0) {
            delete cb_;
        }
    }

    cb_ = nullptr;
}

WeakPtr::WeakPtr() = default;

WeakPtr::WeakPtr(const SharedPtr& sp) : cb_(sp.GetControlBlock()) {
    if (cb_) {
        ++cb_->weak_cnt;
    }
}

WeakPtr::WeakPtr(const WeakPtr& other) : cb_(other.cb_) {
    if (cb_) {
        ++cb_->weak_cnt;
    }
}

WeakPtr::WeakPtr(WeakPtr&& other) noexcept : cb_(other.cb_) {
    other.cb_ = nullptr;
}

WeakPtr::~WeakPtr() {
    Release();
}

WeakPtr& WeakPtr::operator=(const WeakPtr& other) {
    if (this != &other) {
        Release();
        cb_ = other.cb_;

        if (cb_) {
            ++cb_->weak_cnt;
        }
    }

    return *this;
}

WeakPtr& WeakPtr::operator=(WeakPtr&& other) noexcept {
    if (this != &other) {
        Release();
        cb_ = other.cb_;

        other.cb_ = nullptr;
    }

    return *this;
}

WeakPtr& WeakPtr::operator=(const SharedPtr& sp) {
    Release();
    cb_ = sp.GetControlBlock();

    if (cb_) {
        ++cb_->weak_cnt;
    }

    return *this;
}

void WeakPtr::Reset() {
    Release();
}

void WeakPtr::Swap(WeakPtr& other) noexcept {
    std::swap(cb_, other.cb_);
}

size_t WeakPtr::UseCount() const {
    return cb_ ? cb_->shared_cnt : 0;
}

bool WeakPtr::Expired() const {
    return !cb_ || cb_->shared_cnt == 0;
}

SharedPtr WeakPtr::Lock() const {
    if (Expired()) {
        return SharedPtr{};
    }

    return SharedPtr(cb_);
}

void WeakPtr::Release() {
    if (!cb_) return;

    if (--cb_->weak_cnt == 0 && cb_->shared_cnt == 0) {
        delete cb_;
    }

    cb_ = nullptr;
}

void Swap(SharedPtr& a, SharedPtr& b) noexcept {
    a.Swap(b);
}

void Swap(WeakPtr& a, WeakPtr& b) noexcept {
    a.Swap(b);
}
