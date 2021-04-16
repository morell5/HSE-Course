#pragma once

#include <type_traits>
#include <utility>

#include "utility.h"

template <typename T>
add_rvalue_reference_t<T> Declval() noexcept;

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

    //могу ли я неявно привести From к To, проверяем через приведение From к параметру To при вызове implicit_cast(To)
    template <typename To, typename From, typename = decltype(ImplicitCast<To>(Declval<From>()))>
    static std::true_type TypeCast(int);

    //если можно явно привести From к To
    template <typename To, typename From, typename = decltype(static_cast<To>(Declval<From>()))>
    static std::integral_constant<bool,
            !IsInvalidBaseToDerivedCast<To, From>::value &&
            !IsInvalidLvalueToRvalueCast<To, From>::value> TypeCast(int64_t);

    template <class, class>
    static std::false_type TypeCast(...);

    //если есть конструктор с n параметрами
    template <class T, class ...Args,
            class = decltype(T(Declval<Args>()...))>
    static std::true_type TestNary(int);
    template <class ..., class...>
    static std::false_type TestNary(...);

    //если есть конструктор с 1 полем
    template <class T, class A, class = decltype(::new T(Declval<A>()))>
    static std::is_destructible<T> TestUnary(int);
    template <class, class>
    static std::false_type TestUnary(...);
};

// LibCppIsConstructible - partial specializations
template <typename T, typename... Args>
struct LibCppIsConstructible {
    using type = decltype(IsConstructibleHelper::TestNary<T, Args...>(0));
};

//конструктор с 1 аргументом
template <typename T, typename A>
struct LibCppIsConstructible<T, A> {
    using type = decltype(IsConstructibleHelper::TestUnary<T, A>(0));
};

//приведение A к T&(lvalue ref)
template <class T, class A>
struct LibCppIsConstructible<T&, A> {
    using type = decltype(IsConstructibleHelper::TypeCast<T&, A>(0));
};

//приведение A к T&&(rvalue ref)
template <class T, class A>
struct LibCppIsConstructible<T&&, A> {
    using type = decltype(IsConstructibleHelper::TypeCast<T&&, A>(0));
};

// LibCppIsConstructible - partial specializations

template <typename T, typename... Args>
struct IsConstructible: LibCppIsConstructible<T, Args...>::type {
//    using type = typename LibCppIsConstructible<T, Args...>::type;
//    static constexpr bool value_ = type::value_;
}; // Your code goes here {...}

template <typename T>
struct IsCopyConstructible: LibCppIsConstructible<T, const T&>::type {
//    using type = typename LibCppIsConstructible<T, add_lvalue_reference_t<add_const_t<T>>>::type;
//    static constexpr bool value = type::value_;
};
