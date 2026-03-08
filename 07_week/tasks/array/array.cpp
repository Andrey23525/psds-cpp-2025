#include "array.hpp"

using size_t = std::size_t;

template <typename T, size_t N>
Array<T, N>::Array(std::initializer_list<T> list) {
    assert(list.size() <= N);
    std::ranges::copy(list.begin(), list.end(), data_);
}

template <typename T, size_t N>
const T& Array<T, N>::operator[](size_t index) const {
    return data_[index];
}

template <typename T, size_t N>
T& Array<T, N>::operator[](size_t index) {
    return data_[index];
}

template <typename T, size_t N>
const T& Array<T, N>::Front() const {
    return data_[0];
}

template <typename T, size_t N>
T& Array<T, N>::Front() {
    return data_[0];
}

template <typename T, size_t N>
const T& Array<T, N>::Back() const {
    return data_[N - 1];
}

template <typename T, size_t N>
T& Array<T, N>::Back() {
    return data_[N - 1];
}

template <typename T, size_t N>
const T* Array<T, N>::Data() const {
    return data_;
}

template <typename T, size_t N>
T* Array<T, N>::Data() {
    return data_;
}

template <typename T, size_t N>
bool Array<T, N>::Empty() const {
    return N == 0;
}

template <typename T, size_t N>
size_t Array<T, N>::Size() const {
    return N;
}

template <typename T, size_t N>
void Array<T, N>::Fill(const T& value) {
    std::ranges::fill(data_, data_ + N, value);
}

template <typename T, size_t N>
void Array<T, N>::Swap(Array& other) {
    std::ranges::swap(data_, other.data_);
}

template <typename T, size_t N>
T* Array<T, N>::begin() {
    return &data_[0];
}

template <typename T, size_t N>
T* Array<T, N>::end() {
    return &data_[N];
}

template <typename T, size_t N>
const T* Array<T, N>::begin() const {
    return &data_[0];
}

template <typename T, size_t N>
const T* Array<T, N>::end() const {
    return &data_[N];
}

template <typename T, size_t N>
const T* Array<T, N>::cbegin() const {
    return &data_[0];
}

template <typename T, size_t N>
const T* Array<T, N>::cend() const {
    return &data_[N];
}

template <typename T, size_t N>
bool operator==(const Array<T, N>& lhs, const Array<T, N>& rhs) {
    return std::ranges::equal(lhs, rhs);
}

template <typename T, size_t N>
bool operator!=(const Array<T, N>& lhs, const Array<T, N>& rhs) {
    return !(lhs == rhs);
}

template <typename T, size_t N>
bool operator<(const Array<T, N>& lhs, const Array<T, N>& rhs) {
    return lhs <=> rhs;
}

template <typename T, size_t N>
bool operator>(const Array<T, N>& lhs, const Array<T, N>& rhs) {
    return rhs < lhs;
}

template <typename T, size_t N>
bool operator<=(const Array<T, N>& lhs, const Array<T, N>& rhs) {
    return !(rhs < lhs);
}

template <typename T, size_t N>
bool operator>=(const Array<T, N>& lhs, const Array<T, N>& rhs) {
    return !(lhs < rhs);
}

template <typename T, size_t N>
auto operator<=>(const Array<T, N>& lhs, const Array<T, N>& rhs) {
    return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <typename T, size_t N>
void swap(Array<T, N>& lhs, Array<T, N>& rhs) noexcept {
    lhs.Swap(rhs);
}

template <size_t I, typename T, size_t N>
T& get(Array<T, N>& arr) {
    return arr[I];
}

template <size_t I, typename T, size_t N>
const T& get(const Array<T, N>& arr) {
    return arr[I];
}

template <size_t I, typename T, size_t N>
T&& get(Array<T, N>&& arr) {
    return std::move(arr[I]);
}
