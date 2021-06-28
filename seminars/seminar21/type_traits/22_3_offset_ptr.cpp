#include <cstdint>
#include <type_traits>

template <typename T, typename U, typename>
struct ISC_IMPL : std::false_type {};

template <typename T, typename U>
struct ISC_IMPL<T, U, decltype(void(static_cast<U>(std::declval<T>())))> : std::true_type {};

template <typename T, typename U>
struct is_static_castable : ISC_IMPL<T, U, void> {};

template <typename T, typename U>
constexpr bool is_static_castable_v = is_static_castable<T, U>::value;

template <bool B>
using bool_if_t = std::enable_if_t<B, bool>;

// Topic: Conditional explicit constructor
// Boost offset_ptr minimal sample

template <typename T>
class offset_ptr {
public:
    explicit offset_ptr(T* p) {
        m_ptr = reinterpret_cast<uintptr_t>(p) - reinterpret_cast<uintptr_t>(this);
    }

    T* ptr() const noexcept {
        return reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(this) + m_ptr);
    }

    // Attempt 4: bool_if_t

    // U* is convertible to T* implicitly
    // 1. define the type
    // 2. check the signature
    template <typename U, bool_if_t<std::is_convertible_v<U*, T*>> = true>
    offset_ptr(const offset_ptr<U>& rhs) : offset_ptr(rhs.ptr()) {}

    // U* is convertible to T* with a static_cast
    // 1. define the type
    // 2. check the signature
    template <typename U, bool_if_t<!is_static_castable_v<U*, T*> && !std::is_convertible_v<U*, T*>> = true>
    explicit offset_ptr(const offset_ptr<U>& rhs) : offset_ptr(static_cast<T*>(rhs.ptr())) {}
    
private:
    uintptr_t m_ptr;
};

int main() {
    return 0;
}
