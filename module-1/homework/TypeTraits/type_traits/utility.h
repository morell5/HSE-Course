# pragma once

#include <type_traits>
#include <utility>

template<typename T>
struct uncvref {
    ...
};

template<typename T>
using uncvref_t = ...;

template<typename T>
struct add_const {
    ...
};

template<typename T>
using add_const_t = ...;

template<typename T>
struct add_lvalue_reference {
    ...
};

template<typename T>
struct add_rvalue_reference {
    ...
};

template<typename T>
using add_lvalue_reference_t = ...

template<typename T>
using add_rvalue_reference_t = ...