#include <iostream>
#include <type_traits>
#include <memory>
#include <chrono>
#include <utility>


struct B {
    B() = delete;
};

struct D {

    template<typename T, typename... Args, typename = decltype(T(std::declval<Args>()...))>
    static std::true_type foo(int);

    template<typename T, typename... Args>
    static std::false_type foo(...);
};


int main() {
    using v = decltype(D::foo<B>(0));
    std::cout << v::value;
    return 0;
}