#include <type_traits>
#include <utility>

template <typename...>
using void_t = void;

template <typename T, typename Enable>
struct ALR_impl {
    using type = T;
};

template <typename T> 
struct ALR_impl<T, void_t<T&>> {
    using type = T&;
};

template <typename T>
struct add_lvalue_reference : ALR_impl<T, void> {};

int main() {
    // add_lvalue_ref<int> == impl<int, void> == impl<int, void_t<int&>>
    return 0;
}