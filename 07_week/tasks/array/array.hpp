#pragma once
#include <initializer_list>
#include <algorithm>

template<typename T, size_t N>
class Array {
private:
    T data_[N];

public:
    Array() = default;
    Array(std::initializer_list<T> list);
    Array(const Array& other) = default;
    Array(Array&& other) noexcept = default;
    Array& operator=(const Array& other) = default;
    Array& operator=(Array&& other) noexcept = default;
    ~Array() = default;

    const T& operator[](size_t index) const;
    T& operator[](size_t index);

    const T& Front() const;
    T& Front();
    const T& Back() const;
    T& Back();
    [[nodiscard]] const T* Data() const;
    [[nodiscard]] T* Data();
    [[nodiscard]] bool Empty() const;
    [[nodiscard]] size_t Size() const;
    void Fill(const T& value);
    void Swap(Array& other);

    T* begin();
    T* end();
    const T* begin() const;
    const T* end() const;
    const T* cbegin() const;
    const T* cend() const;
};

template<typename T, size_t N>
bool operator==(const Array<T, N>& lhs, const Array<T, N>& rhs);

template<typename T, size_t N>
bool operator!=(const Array<T, N>& lhs, const Array<T, N>& rhs);

template<typename T, size_t N>
bool operator<(const Array<T, N>& lhs, const Array<T, N>& rhs);

template<typename T, size_t N>
bool operator>(const Array<T, N>& lhs, const Array<T, N>& rhs);

template<typename T, size_t N>
bool operator<=(const Array<T, N>& lhs, const Array<T, N>& rhs);

template<typename T, size_t N>
bool operator>=(const Array<T, N>& lhs, const Array<T, N>& rhs);

template<typename T, size_t N>
auto operator<=>(const Array<T, N>& lhs, const Array<T, N>& rhs);

template<typename T, size_t N>
void swap(Array<T, N>& lhs, Array<T, N>& rhs) noexcept;

template<size_t I, typename T, size_t N>
T& get(Array<T, N>& arr);

template<size_t I, typename T, size_t N>
const T& get(const Array<T, N>& arr);

template<size_t I, typename T, size_t N>
T&& get(Array<T, N>&& arr);