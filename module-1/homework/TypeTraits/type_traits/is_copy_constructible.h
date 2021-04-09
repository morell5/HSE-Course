#pragma once

#include <type_traits>
#include <utility>

#include "utility.h"

//<<<<<<< HEAD
//template <typename T>
//std::add_rvalue_reference_t<T> Declval() noexcept;
//
//template<typename T, typename... Args>
//struct is_constructible_impl;
//
////TO = derived
////from = base
//template<typename Derived, typename Base>
//struct is_invalid_base_to_derived_cast {
//    using Base_ = uncvref_t<Base>;
//    using Derived_ = uncvref_t<Derived>;
//
//    static std::integral_constant<bool,
//        !std::is_same_v<Base_, Derived_> &&
//        std::is_base_of_v<Base_, Derived_> &&
//        !is_constructible_impl<Derived_, Base>::type::value>
//    value;
//};
////
//template<typename To, typename From>
//struct is_invalid_lvalue_to_rvalue_cast : std::false_type {
//
//};
//
//template<typename RefTo, typename RefFrom>
//struct is_invalid_lvalue_to_rvalue_cast<RefTo&&, RefFrom&> {
//    using From_ = uncvref_t<RefFrom>;
//    using To_ = uncvref_t<RefTo>;
//
//    static std::integral_constant<bool,
//        std::is_same_v<From_, To_> &&
//        std::is_base_of_v<To_, From_>>
//    value;
//};
//
//struct is_constructible_helper {
//    template<typename To>
//    static void implicit_cast(To);
//
//    //могу ли я неявно привести From к To, проверяем через приведение From к параметру To при вызове implicit_cast(To)
//    template<typename To, typename From, typename = decltype(implicit_cast<To>(Declval<From>()))>
//    static std::true_type type_cast(int);
//
//    //если можно явно привести From к To
//    template<typename To, typename From, typename = decltype(static_cast<To>(Declval<From>()))>
//    static std::integral_constant<bool,
//            !is_invalid_base_to_derived_cast<To, From>::value &&
//            !is_invalid_lvalue_to_rvalue_cast<To, From>::value> type_cast(long);
//
//    template <class, class>
//    static std::false_type type_cast(...);
//
//    //если есть конструктор с n параметрами
//    template <class T, class ...Args,
//            class = decltype(T(Declval<Args>()...))>
//    static std::true_type test_nary(int);
//    template <class ..., class...>
//    static std::false_type test_nary(...);
//
//    //если есть конструктор с 1 полем
//    template <class T, class A, class = decltype(::new T(Declval<A>()))>
//    static std::is_destructible<T> test_unary(int);
//    template <class, class>
//    static std::false_type test_unary(...);
//};
//
//template<typename T, typename... Args>
//struct is_constructible_impl {
//    using type = decltype(is_constructible_helper::test_nary<T, Args...>(0));
//};
//
////конструктор с 1 аргументом
//template<typename T, typename A>
//struct is_constructible_impl<T, A> {
//    using type = decltype(is_constructible_helper::test_unary<T, A>(0));
//};
//
////приведение A к T&(lvalue ref)
//template <class T, class A>
//struct is_constructible_impl<T&, A> {
//    using type = decltype(is_constructible_helper::type_cast<add_lvalue_reference_t<T>, A>(0));
//    static constexpr bool value = type::value;
//};
//
////приведение A к T&&(rvalue ref)
//template <class T, class A>
//struct is_constructible_impl<T&&, A> {
//    using type = decltype(is_constructible_helper::type_cast<add_rvalue_reference_t<T>, A>(0));
//    static constexpr bool value = type::value;
//};
//
//template<typename T, typename... Args>
//struct is_constructible {
//    using type = typename is_constructible_impl<T, Args...>::type;
//    static constexpr bool value = type::value;
//};
//
//template<typename T>
//struct is_copy_constructible {
//    using type = typename is_constructible<T, add_lvalue_reference_t<add_const_t<T>>>::type;
//    static constexpr bool value = type::value;
//};
//=======
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
    template<typename To>
    static void ImplicitCast(To);

    //могу ли я неявно привести From к To, проверяем через приведение From к параметру To при вызове implicit_cast(To)
    template<typename To, typename From, typename = decltype(ImplicitCast<To>(Declval<From>()))>
    static std::true_type TypeCast(int);

    //если можно явно привести From к To
    template<typename To, typename From, typename = decltype(static_cast<To>(Declval<From>()))>
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
template<typename T, typename... Args>
struct LibCppIsConstructible {
    using type = decltype(IsConstructibleHelper::TestNary<T, Args...>(0));
};

//конструктор с 1 аргументом
template<typename T, typename A>
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
