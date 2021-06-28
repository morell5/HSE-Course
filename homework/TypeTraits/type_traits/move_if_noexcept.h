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
// Your code goes here
// Conditional - partial specialization

template <typename T, typename F>
struct Conditional<true, T, F> {
    using type = T;
};

template <bool condition, typename T, typename F>
using conditional_v = // Your code goes here

// MoveIfNoExcept
// Your code goes here
// MoveIfNoExcept