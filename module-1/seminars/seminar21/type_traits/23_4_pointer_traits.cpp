#include <cstdint>
#include <iostream>
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

    // Attempt 4: add & after enable_if_t evaluation
    // Pros: it compiles
    // Cons: it leads to segfault
    template <bool B = std::is_void_v<T>, typename TR = std::enable_if_t<!B, T>&>
    static auto PointerTo(TR r) {
        return &r;
    }
};

int main() {
    int32_t x = 1;
    
    int32_t* ptr_x = PointerTraits<int32_t*>::PointerTo(x);    
    void* ptr_void = PointerTraits<void*>::PointerTo(x);

    // UB: Segfault (GCC: 9.2.0):
    std::cout << *ptr_x;
    return 0;
}