#include <type_traits>
#include <utility>

template <typename T>
struct add_lvalue_reference {
    using type = T&;
};

template <>
struct add_lvalue_reference<void> {
    using type = void;
};

template <>
struct add_lvalue_reference<const void> {

};

template <>
struct add_lvalue_reference<volatile void> {

};

template <>
struct add_lvalue_reference<const volatile void> {

};

template <typename T>
using add_lvalue_reference_t = typename add_lvalue_reference<T>::type;

int main() {
    // Now it works, but it's naive =(
    static_assert( std::is_same_v<add_lvalue_reference_t<void>, void> );
    // Motivation: make compiler add reference if and only if it would caused an error
    return 0;
}