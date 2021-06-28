#include <cstdint>
#include <type_traits>

template <typename T>
struct PointerTraits;

template <typename T>
struct PointerTraits<T*> {
    using pointer = T*;
    using element_type = T;
    using difference_type = std::ptrdiff_t;

    template <typename U>
    using rebind = U*;

    // Attempt 2: use std::is_void_v + std::enable_if_t
    // Result: CE again
    // Reson: function signature is argly evaluated (T& evaluates early than std::is_void_v + std::enable_if_t)
    template <bool B = std::is_void_v<T>, typename = std::enable_if_t<!B>>
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