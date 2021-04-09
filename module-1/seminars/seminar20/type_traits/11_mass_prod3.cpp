#include <iostream>
#include <type_traits>
#include <tuple>

template<typename T, typename, typename...>
struct IC_IMPL : std::false_type {};

template <typename T, typename... Ts>
struct IC_IMPL<T, decltype(void(::new T(std::declval<Ts>()...))), Ts...> : std::true_type {
    constexpr static auto t = std::tuple<Ts...>();
};

template <typename T, typename... Ts>
struct is_constructible : IC_IMPL<T, void, Ts...> {};

struct Foo {
    Foo(int,double);
};

int main() {
    auto t = is_constructible<Foo, int, double>::t;
    // void maps to second parameter -> decltype(void(::new T(std::declval<Ts>()...)))
    // there is no void in Ts...
    std::cout << std::is_same<decltype(t), std::tuple<int, double>>::value;
    return 0;
}