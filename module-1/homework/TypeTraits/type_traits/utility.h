#pragma once

#include <type_traits>
#include <utility>

template <typename T>
struct RemoveConst {
    using type = T;
};

template <typename T>
struct RemoveConst<T const> {
    using type = T;
};

template <typename T>
using remove_const_t = typename RemoveConst<T>::type;

template <typename T>
struct RemoveVolatile {
    using type = T;
};

template <typename T>
struct RemoveVolatile<T volatile> {
    using type = T;
};

template <typename T>
using remove_volatile_t = typename RemoveVolatile<T>::type;

template <typename T>
struct RemoveReference {
    using type = T;
};

template <typename T>
struct RemoveReference<T&> {
    using type = T;
};

template <typename T>
struct RemoveReference<T&&> {
    using type = T;
};

template <typename T>
using remove_reference_t = typename RemoveReference<T>::type;

template <typename T>
struct Uncv {
    using type = remove_const_t<remove_volatile_t<T>>;
};

template <typename T>
using uncv_t = typename Uncv<T>::type;

template <typename T>
struct Uncvref {
    using type = uncv_t<remove_reference_t<T>>;
};

template <typename T>
using uncvref_t = typename Uncvref<T>::type;

template <typename T>
struct AddConst {
    using type = const T;
};

template <typename T>
using add_const_t = typename AddConst<T>::type;

template <typename T>
struct AddLvalueReference {
    using type = T&;
};

template <typename T>
struct AddRvalueReference {
    using type = T&&;
};

template <typename T>
using add_lvalue_reference_t = typename AddLvalueReference<T>::type;

template <typename T>
using add_rvalue_reference_t = typename AddRvalueReference<T>::type;

template <typename T>
add_rvalue_reference_t<T> Declval() noexcept;
