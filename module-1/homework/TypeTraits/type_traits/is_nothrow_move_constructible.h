#pragma once 

#include <type_traits>

#include "is_copy_constructible.h"
#include "utility.h"

//<is_constructible, is_reference, T, Args...>
template<bool, bool, typename T, typename... Args> struct is_nothrow_constructible_impl;

// is_nothrow_constructible_impl - partial specializations
...

template<typename T, typename... Args>
struct is_nothrow_constructible {
    ...
};

template<typename T, std::size_t N>
struct is_nothrow_constructible<T[N]> {
    ...
};

template<typename T>
struct is_nothrow_move_constructible {
    ...
};