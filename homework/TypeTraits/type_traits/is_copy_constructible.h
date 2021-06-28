#pragma once

#include <type_traits>
#include <utility>

#include "utility.h"

template <typename T, typename... Args>
struct LibCppIsConstructible;

template <typename Derived, typename Base>
struct IsInvalidBaseToDerivedCast {
    // Your code goes here
};

template <typename To, typename From>
struct IsInvalidLvalueToRvalueCast : std::false_type {
    // Your code goes here
};

template <typename RefTo, typename RefFrom>
struct IsInvalidLvalueToRvalueCast<RefTo&&, RefFrom&> {
    // Your code goes here
};

struct IsConstructibleHelper {
    // Your code goes here
};

// LibCppIsConstructible - partial specializations
// Your code goes here
// LibCppIsConstructible - partial specializations

template <typename T, typename... Args>
struct IsConstructible : // Your code goes here {...}

template <typename T>
struct IsCopyConstructible : // Your code goes here {...}