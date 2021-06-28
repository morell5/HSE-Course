#include <iostream>

template <typename T>
struct PointerTraits;

template <typename T>
struct PointerTraits<T*> {
    using pointer = T*;
    using element_type = T;
    using difference_type = std::ptrdiff_t;

    template <typename U>
    using rebind = U*;

    // Attempt 1:
    // Cons: T=void -> void& -> CE
    static auto PointerTo(T& r) {
        return &r;
    }
};

int main() {
    int32_t x = 1;

    int32_t* ptr_x = PointerTraits<int32_t*>::PointerTo(x);
    void* ptr_void = PointerTraits<void*>::PointerTo(x);
    return 0;
}