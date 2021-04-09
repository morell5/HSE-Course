#pragma once

#include <type_traits>

#include "is_copy_constructible.h"
#include "utility.h"

//<IsConstructible, is_reference, T, Args...>
template <bool, bool, typename T, typename... Args>
struct LibCppIsNoThrowConstructible;

struct LibCppIsNoThrowConstructibleHelper {
    template<typename To>
    static void ImplicitCast(To);
};

//если не ссылка, то смотрим на noexcept(expression), где expression - наш конструктор
template<typename T, typename... Args>
struct LibCppIsNoThrowConstructible<true, false, T, Args...> {
    using type = std::integral_constant<bool, noexcept(T(Declval<Args>()...))>;
};

//если это ссылка, то проверяем каст
template<typename T, typename A>
struct LibCppIsNoThrowConstructible<true, true, T, A> {
    using type = std::integral_constant<bool, noexcept(LibCppIsNoThrowConstructibleHelper::ImplicitCast<T>(Declval<A>()))>;
};

template<bool IsRef, typename T, typename... Args>
struct LibCppIsNoThrowConstructible<false, IsRef, T, Args...> {
    using type = std::false_type;
};

template <typename T, typename... Args>
struct IsNoThrowConstructible
        : LibCppIsNoThrowConstructible<IsConstructible<T, Args...>::value, std::is_reference_v<T>, T, Args...>::type {
}; // Your code goes here {...}

template <typename T, std::size_t N>
struct IsNoThrowConstructible<T[N]>
        : LibCppIsNoThrowConstructible<IsConstructible<T>::value, std::is_reference_v<T>, T>::type {
};

template <typename T>
struct IsNoThrowMoveConstructible : IsNoThrowConstructible<T, T&&> {
};
