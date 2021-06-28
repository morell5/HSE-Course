#include <iostream>
#include <type_traits>
#include <utility>

template <typename T, typename U, typename Enable>
struct is_assignable_impl : std::false_type {};

template <typename T, typename U>
// is_assignable_impl<T, U, void> resolution algo:
// 1. ensure well-formedness std::declval<T>() = std::declval<U>()
// 2. cast expression to void
// 3. use void as third parameter (decltype)
// 4. add spec as candidate

struct is_assignable_impl< T, U, decltype(static_cast<void>( std::declval<T>() = std::declval<U>() ))> : std::true_type {};

template <typename T, typename U>
struct is_assignable : is_assignable_impl<T, U, void> {};

int main() {
    std::cout << is_assignable<int&, int>::value;
    return 0;
}