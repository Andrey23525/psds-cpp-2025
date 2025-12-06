#include <stdexcept>

template <typename Predicate>
const int* FindLastElement(const int* begin, const int* end, Predicate pred) {
	if (begin == nullptr || end == nullptr || begin > end) {
        return end;
    }
	for (const int* ptr = end - 1; ptr >= begin; --ptr) {
        if (pred(*ptr)) {
            return ptr;
        }
    }
    return end;
}