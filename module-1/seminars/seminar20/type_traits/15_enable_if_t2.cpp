#include <iostream>
#include <type_traits>

template<bool B, typename T>
struct EnableIf {
    using type = T;
};

template<typename T>
struct EnableIf<false, T> {};

template <bool B, typename T>
using EnableIfT = typename EnableIf<B, T>::type;

// EnableIfT is an opposite to partial specializations with SFINAE
// EnableIfT maps:
// true -> well-formed expression
// false -> ill-formed expression

//  partial specializations with SFINAE maps:
// well-formed expression -> true
// ill-formed expression -> false


// Via structs

template <typename T, typename>
struct IP_IMPL : std::false_type {};

template <typename T>
struct IP_IMPL<T, decltype(dynamic_cast<void*>(std::declval<std::remove_cv_t<T>>()))> : std::true_type {};


template <typename T>
// IP_IMPL<T, void*> well-formed -> true
// IP_IMPL<T, void*> ill-formed -> false 
struct is_polymorhic_via_structs : IP_IMPL<T, void*> {};

int main() {
    return 0;
}