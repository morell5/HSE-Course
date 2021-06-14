#pragma once

#include <type_traits>

#include "is_copy_constructible.h"
#include "utility.h"

template <bool, bool, typename T, typename... Args>
struct LibCppIsNoThrowConstructible;

template <typename T, typename... Args>
struct LibCppIsNoThrowConstructible<true, false, T, Args...> {
    using type = std::integral_constant<bool, noexcept(T(Declval<Args>()...))>;
};

template <typename T, typename Arg>
struct LibCppIsNoThrowConstructible<true, true, T, Arg> {
    using type =
        std::integral_constant<bool,
                               noexcept(IsConstructibleHelper::ImplicitCast<T>(Declval<Arg>()))>;
};

template <bool IsReference, typename T, typename... Args>
struct LibCppIsNoThrowConstructible<false, IsReference, T, Args...> {
    using type = std::false_type;
};

template <typename T, typename... Args>
struct IsNoThrowConstructible
    : LibCppIsNoThrowConstructible<IsConstructible<T, Args...>::value, std::is_reference_v<T>, T,
                                   Args...>::type {};

template <typename T, std::size_t N>
struct IsNoThrowConstructible<T[N]>
    : LibCppIsNoThrowConstructible<IsConstructible<T>::value, std::is_reference_v<T>, T>::type {};

template <typename T>
struct IsNoThrowMoveConstructible : IsNoThrowConstructible<T, T&&> {};
