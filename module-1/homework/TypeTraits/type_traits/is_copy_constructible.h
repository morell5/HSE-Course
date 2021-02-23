# pragma once

#include <type_traits>
#include <utility>

#include "utility.h"

template<typename T, typename... Args>
struct is_constructible_impl;

template<typename Derived, typename Base>
struct is_invalid_base_to_derived_cast {
   ...
};

template<typename To, typename From>
struct is_invalid_lvalue_to_rvalue_cast : std::false_type {
    ...
};

template<typename RefTo, typename RefFrom>
struct is_invalid_lvalue_to_rvalue_cast<RefTo&&, RefFrom&> {
    ...
};

struct is_constructible_helper {
    ...
};

template<typename T, typename... Args>
struct is_constructible_impl {
    ...
};

// is_constructible_impl - partial specializations
...

template<typename T, typename... Args>
struct is_constructible {...};

template<typename T>
struct is_copy_constructible {...};