#pragma once 

#include <type_traits>

#include "is_copy_constructible.h"
#include "utility.h"

//<is_constructible, is_reference, T, Args...>
template<bool, bool, typename T, typename... Args> struct is_nothrow_constructible_impl;


struct is_nothrow_constructible_helper {
    template<typename To>
    static void implicit_cast(To);
};

//если не ссылка, то смотрим на noexcept(expression), где expression - наш конструктор
template<typename T, typename... Args>
struct is_nothrow_constructible_impl<true, false, T, Args...> {
    static bool constexpr value = std::integral_constant<bool, noexcept(T(declval<Args>()...))>::value;
};

//если это ссылка, то проверяем каст
template<typename T, typename A>
struct is_nothrow_constructible_impl<true, true, T, A> {
    static bool constexpr value = std::integral_constant<bool, noexcept(is_nothrow_constructible_helper::implicit_cast<T>(declval<A>()))>::value;
};

template<bool IsRef, typename T, typename... Args>
struct is_nothrow_constructible_impl<false, IsRef, T, Args...>: public std::false_type {};

template<typename T, typename... Args>
struct is_nothrow_constructible {
    static bool constexpr value = is_nothrow_constructible_impl<is_constructible<T, Args...>::value, std::is_reference_v<T>, T, Args...>::value;
};

template<typename T, std::size_t N>
struct is_nothrow_constructible<T[N]> {
    static bool constexpr value = is_nothrow_constructible_impl<is_constructible<T>::value, std::is_reference_v<T>, T>::value ;
};

template<typename T>
struct is_nothrow_move_constructible {
    static bool constexpr value = is_nothrow_constructible<T, T&&>::value;
};