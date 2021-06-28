#include <type_traits>
#include <utility>

template <typename T>
struct add_lvalue_reference {
    using type = T&;
};

template <typename T>
using add_lvalue_reference_t = typename add_lvalue_reference<T>::type;

int main() {
    // It is ok, but what about void?
    static_assert( std::is_same_v<add_lvalue_reference_t<int&&>, int&> );
    static_assert( std::is_same_v<add_lvalue_reference_t<int&>, int&> );
    static_assert( std::is_same_v<add_lvalue_reference_t<int>, int&> );
    // CE: forming reference to void
    static_assert( std::is_same<add_lvalue_reference_t<void>, void> );
    // Solution: partial spec comes to the rescue
    return 0;
}