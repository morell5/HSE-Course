#include <type_traits>

template<typename T, typename, typename...>
struct INCTImpl : std::false_type {};

// we use std::bool_constant to store noexcept result
template<typename T, typename... Us>
struct INCTImpl<T, decltype(void(::new  T(std::declval<Us>()...))), Us...> : 
std::bool_constant<noexcept(::new  T(std::declval<Us>()...))> {};

template<typename T, typename... Us>
struct IsNothrowConstructible : INCTImpl<T, void, Us...> {};

int main() {
    return 0;
}