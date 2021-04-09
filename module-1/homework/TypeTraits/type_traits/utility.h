#pragma once

#include <type_traits>
#include <utility>

//<<<<<<< HEAD
//template<typename T>
//struct remove_cv {
//    using type = T;
//};
//template<typename T>
//struct remove_cv<const T> {
//    using type = T;
//};
//template<typename T>
//struct remove_cv<volatile T> {
//    using type = T;
//};
//template<typename T>
//struct remove_cv<const volatile T> {
//    using type = T;
//};
//
//template<typename T>
//struct remove_reference {
//    using type = T;
//};
//
//template<typename T>
//struct remove_reference<T&> {
//    using type = T;
//};
//
//template<typename T>
//struct remove_reference<T&&> {
//    using type = T;
//};
//
//template<typename T>
//struct uncvref {
//    using type = typename remove_cv<typename remove_reference<T>::type>::type;
//};
//
//template<typename T>
//using uncvref_t = typename uncvref<T>::type;
//
//template<typename T>
//struct add_const {
//    using type = const T;
//};
//
//template<typename T>
//using add_const_t = typename add_const<T>::type ;
//
//template<typename T>
//struct add_lvalue_reference {
//    using type = T&;
//};
//
//template<typename T>
//struct add_rvalue_reference {
//    using type = T&&;
//};
//
//template<typename T>
//using add_lvalue_reference_t = typename add_lvalue_reference<T>::type;
//
//template<typename T>
//using add_rvalue_reference_t = typename add_rvalue_reference<T>::type;
//=======
template<typename T>
struct Removecv {
    using type = T;
};
template<typename T>
struct Removecv<const T> {
    using type = T;
};
template<typename T>
struct Removecv<volatile T> {
    using type = T;
};
template<typename T>
struct Removecv<const volatile T> {
    using type = T;
};

template<typename T>
struct RemoveReference {
    using type = T;
};

template<typename T>
struct RemoveReference<T&> {
    using type = T;
};

template<typename T>
struct RemoveReference<T&&> {
    using type = T;
};
template <typename T>
struct Uncvref {
    using type = typename Removecv<typename RemoveReference<T>::type>::type;
};

template <typename T>
using uncvref_t = typename Uncvref<T>::type;// Your code goes here

template <typename T>
struct AddConst {
    using type = const T;// Your code goes here
};

template <typename T>
using add_const_t = typename AddConst<T>::type;// Your code goes here

template <typename T>
struct AddLvalueReference {
    using type = T&;
}; // Your code goes here

template <typename T>
struct AddRvalueReference {
    using type = T&&;
}; // Your code goes here

template <typename T>
using add_lvalue_reference_t = typename AddLvalueReference<T>::type;// Your code goes here

template <typename T>
using add_rvalue_reference_t = typename AddRvalueReference<T>::type;// Your code goes here
