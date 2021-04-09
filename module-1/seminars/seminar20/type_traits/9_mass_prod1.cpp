#include <type_traits>

// Via functions

template <typename T, typename U, typename>
struct ISC_IMPL : std::false_type {};

template <typename T, typename U>
struct ISC_IMPL<T, U, decltype(void(static_cast<U>(std::declval<T>())))> : std::true_type {};

template <typename T, typename U>
struct is_static_castable : ISC_IMPL<T, U, void> {};

int main() {
    return 0;
}