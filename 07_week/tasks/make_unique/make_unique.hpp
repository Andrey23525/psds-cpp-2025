#pragma once
#include <memory>

template <typename T, typename... Args>
std::unique_ptr<T> MakeUnique(Args&&... args);