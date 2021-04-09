#pragma once

#include <type_traits>

#include "is_copy_constructible.h"
#include "utility.h"

//<IsConstructible, is_reference, T, Args...>
template <bool, bool, typename T, typename... Args>
struct LibCppIsNoThrowConstructible;

// LibCppIsNoThrowConstructible - partial specializations
// Your code goes here
// LibCppIsNoThrowConstructible - partial specializations

template <typename T, typename... Args>
struct IsNoThrowConstructible : // Your code goes here {...}

template <typename T, std::size_t N>
struct IsNoThrowConstructible<T[N]> : // Your code goes here {...}

template <typename T>
struct IsNoThrowMoveConstructible : // Your code goes here {...}