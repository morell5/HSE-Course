# pragma once

#include <type_traits>
#include <utility>

#include "is_copy_constructible.h"
#include "is_nothrow_move_constructible.h"
#include "utility.h"

// conditional
template<bool condition, typename T, typename F>
struct conditional;

template<typename T, typename F>
struct conditional<true, T, F> {
    using type = T;
};

template<typename T, typename F>
struct conditional<false, T, F> {
    using type = F;
};

template<bool condition, typename T, typename F>
using conditional_v = typename conditional<condition, T, F>::type;

// move_if_noexcept

template<typename T>
conditional_v<
        !is_nothrow_move_constructible<T>::value && is_copy_constructible<T>::value,
        add_lvalue_reference_t<add_const_t<T>>,
        add_rvalue_reference_t<T>> move_if_noexcept(T& t) noexcept {
    return std::move(t);
}

