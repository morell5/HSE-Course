#pragma once

#include <type_traits>
#include <utility>

#include "is_copy_constructible.h"
#include "is_nothrow_move_constructible.h"
#include "utility.h"

template <bool condition, typename T, typename F>
struct Conditional {
    // Your code goes here
};

// Conditional - partial specialization
template <typename T, typename F>
struct Conditional<false, T, F> {
    using type = F;
};
// Conditional - partial specialization

template <typename T, typename F>
struct Conditional<true, T, F> {
    using type = T;
};

template <bool condition, typename T, typename F>
using conditional_v = typename Conditional<condition, T, F>::type;

// MoveIfNoExcept

template <typename T>
conditional_v<
        !IsNoThrowMoveConstructible<T>::value && IsCopyConstructible<T>::value,
        const T&,
        T&&>
MoveIfNoExcept(T& t) {
    return std::move(t);
}

// MoveIfNoExcept
