#pragma once

#include <type_traits>
#include <utility>

template <typename T>
struct Uncvref {
    // Your code goes here
};

template <typename T>
using uncvref_t = // Your code goes here

template <typename T>
struct AddConst {
    using type = // Your code goes here
};

template <typename T>
using add_const_t = // Your code goes here

template <typename T>
struct AddLvalueReference : // Your code goes here

template <typename T>
struct AddRvalueReference : // Your code goes here

template <typename T>
using add_lvalue_reference_t = // Your code goes here

template <typename T>
using add_rvalue_reference_t = // Your code goes here