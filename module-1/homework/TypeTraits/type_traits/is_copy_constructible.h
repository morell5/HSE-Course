# pragma once

#include <type_traits>
#include <utility>

#include "utility.h"

template <typename T>
std::add_rvalue_reference_t<T> declval() noexcept;

template<typename T, typename... Args>
struct is_constructible_impl;

//TO = derived
//from = base
template<typename Derived, typename Base>
struct is_invalid_base_to_derived_cast {
    using Base_ = uncvref_t<Base>;
    using Derived_ = uncvref_t<Derived>;

    static std::integral_constant<bool,
        !std::is_same_v<Base_, Derived_> &&
        std::is_base_of_v<Base_, Derived_> &&
        !is_constructible_impl<Derived_, Base>::type::value>
    value;
};
//
template<typename To, typename From>
struct is_invalid_lvalue_to_rvalue_cast : std::false_type {

};

template<typename RefTo, typename RefFrom>
struct is_invalid_lvalue_to_rvalue_cast<RefTo&&, RefFrom&> {
    using From_ = uncvref_t<RefFrom>;
    using To_ = uncvref_t<RefTo>;

    static std::integral_constant<bool,
        std::is_same_v<From_, To_> &&
        std::is_base_of_v<To_, From_>>
    value;
};

struct is_constructible_helper {
    template<typename To>
    static void implicit_cast(To);

    //могу ли я неявно привести From к To, проверяем через приведение From к параметру To при вызове implicit_cast(To)
    template<typename To, typename From, typename = decltype(implicit_cast<To>(declval<From>()))>
    static std::true_type type_cast(int);

    //если можно явно привести From к To
    template<typename To, typename From, typename = decltype(static_cast<To>(declval<From>()))>
    static std::integral_constant<bool,
            !is_invalid_base_to_derived_cast<To, From>::value &&
            !is_invalid_lvalue_to_rvalue_cast<To, From>::value> type_cast(long);

    template <class, class>
    static std::false_type type_cast(...);

    //если есть конструктор с n параметрами
    template <class T, class ...Args,
            class = decltype(T(declval<Args>()...))>
    static std::true_type test_nary(int);
    template <class ..., class...>
    static std::false_type test_nary(...);

    //если есть конструктор с 1 полем
    template <class T, class A, class = decltype(::new T(declval<A>()))>
    static std::is_destructible<T> test_unary(int);
    template <class, class>
    static std::false_type test_unary(...);
};

template<typename T, typename... Args>
struct is_constructible_impl {
    using type = decltype(is_constructible_helper::test_nary<T, Args...>(0));
};

//конструктор с 1 аргументом
template<typename T, typename A>
struct is_constructible_impl<T, A> {
    using type = decltype(is_constructible_helper::test_unary<T, A>(0));
};

//приведение A к T&(lvalue ref)
template <class T, class A>
struct is_constructible_impl<T&, A> {
    using type = decltype(is_constructible_helper::type_cast<add_lvalue_reference_t<T>, A>(0));
    static constexpr bool value = type::value;
};

//приведение A к T&&(rvalue ref)
template <class T, class A>
struct is_constructible_impl<T&&, A> {
    using type = decltype(is_constructible_helper::type_cast<add_rvalue_reference_t<T>, A>(0));
    static constexpr bool value = type::value;
};

template<typename T, typename... Args>
struct is_constructible {
    using type = typename is_constructible_impl<T, Args...>::type;
    static constexpr bool value = type::value;
};

template<typename T>
struct is_copy_constructible {
    using type = typename is_constructible<T, add_lvalue_reference_t<add_const_t<T>>>::type;
    static constexpr bool value = type::value;
};