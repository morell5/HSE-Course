#include <iostream>
#include <type_traits>
#include <utility>

template<typename T, typename A, typename = decltype(::new T(std::declval<A>()))>    
static std::true_type unary(int);

template<typename, typename>
static std::false_type unary(...);

struct S {
    S(int x) {};
    ~S() = delete;
    
    static int v;
};

int main() {
    using T = S;
    using A = int;
    std::cout << std::is_destructible<T>::value << std::endl;
    std::cout << std::is_constructible<T, A>::value << std::endl;
    std::cout << decltype(unary<T, A>(0))::value;
    return 0;
}