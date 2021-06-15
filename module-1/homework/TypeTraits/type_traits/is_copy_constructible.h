#pragma once

#include <type_traits>
#include <utility>

#include "utility.h"

template <typename T, typename... Args>
struct LibCppIsConstructible;

template <typename Derived, typename Base>
struct IsInvalidBaseToDerivedCast {
    using base = uncvref_t<Base>;
    using derived = uncvref_t<Derived>;

    static std::integral_constant<bool,
        !std::is_same_v<base, derived> &&
        std::is_base_of_v<base, derived> &&
        !LibCppIsConstructible<derived, Base>::type::value>
    value_;
};

template <typename To, typename From>
struct IsInvalidLvalueToRvalueCast : std::false_type {
    // Your code goes here
};

template <typename RefTo, typename RefFrom>
struct IsInvalidLvalueToRvalueCast<RefTo&&, RefFrom&> {
    using from = uncvref_t<RefFrom>;
    using to = uncvref_t<RefTo>;

    static std::integral_constant<bool,
            std::is_same_v<from, to> &&
            std::is_base_of_v<to, from>>
            value_;
};

struct IsConstructibleHelper {
    template <typename To>
    static void ImplicitCast(To);

    template <typename To, typename From, typename = decltype(ImplicitCast<To>(Declval<From>()))>
    static std::true_type Castable(int);

    template <typename To, typename From, typename = decltype(static_cast<To>(Declval<From>()))>
    static std::integral_constant<bool, !IsInvalidBaseToDerivedCast<To, From>::value &&
                                            !IsInvalidLvalueToRvalueCast<To, From>::value>
    Castable(double);

    template <typename, typename>
    static std::false_type Castable(...);

    template <typename T, typename... Args, typename = decltype(T(Declval<Args>()...))>
    static std::true_type Constructible(int);

    template <typename, typename>
    static std::false_type Constructible(...);
};

template <typename T, typename... Args>
struct LibCppIsConstructible {
    using type = decltype(IsConstructibleHelper::Constructible<T, Args...>(0));
};

template <typename T, typename Arg>
struct LibCppIsConstructible<T, Arg> {
    using type = decltype(IsConstructibleHelper::Constructible<T, Arg>(0));
};

template <typename T, typename Arg>
struct LibCppIsConstructible<T&, Arg> {
    using type = decltype(IsConstructibleHelper::Castable<T&, Arg>(0));
};

template <typename T, typename Arg>
struct LibCppIsConstructible<T&&, Arg> {
    using type = decltype(IsConstructibleHelper::Castable<T&&, Arg>(0));
};

template <typename T, typename... Args>
struct IsConstructible : LibCppIsConstructible<T, Args...>::type {};

template <typename T>
struct IsCopyConstructible : LibCppIsConstructible<T, const T&>::type {};