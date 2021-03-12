#include <type_traits>
#include <utility>

template <typename...>
using void_t = void;

template <typename T, typename>
struct ALR_impl {
    using type = T;
};

template <typename T>
struct ALR_impl<T, void_t<T&>> {
    using type = T&;
};

template <typename T, typename>
struct ARR_impl {
    using type = T;
};

template <typename T>
struct ARR_impl<T, void_t<T&&>> {
    using type = T&&;
};


template <typename T>
struct add_lvalue_reference : ALR_impl<T, void> {};

template <typename T>
struct add_rvalue_reference : ARR_impl<T, void> {};

int main() {
    return 0;
}