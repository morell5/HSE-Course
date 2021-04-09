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

    // Attempt 5: add constraint to template parameter (std::enable_if_t<!B, T>)
    template <bool B = std::is_void_v<T>>
    static auto PointerTo(std::enable_if_t<!B, T>& r) {
        return &r;
    }
};

int main() {
    int32_t x = 1;

    int32_t* ptr_x = PointerTraits<int32_t*>::PointerTo(x);
    void* ptr_void = PointerTraits<void*>::PointerTo(x);
    return 0;
}