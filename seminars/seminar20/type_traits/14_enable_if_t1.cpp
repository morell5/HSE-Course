#include <iostream>
#include <string>
#include <type_traits>

template<bool B, typename T=void>
struct EnableIf {
    using type = T;  
};

template<typename T>
// Simplification from Conditional: Conditional<false, T, F> -> Conditional<false, T> 
// {    using type = F;  } -> {}
struct EnableIf<false, T> {};

template<bool B, typename T=void>
using EnableIfT = typename EnableIf<B, T>::type;

template<class T, class Enable = void>
struct A {
    std::string name = "primary";
}; 
 
template<class T>
struct A<T, EnableIfT<std::is_floating_point<T>::value>> {
    std::string name = "spec";
};
 

int main() {
    std::cout << A<int>().name << std::endl;
    std::cout << A<double>().name << std::endl;
    return 0;
}