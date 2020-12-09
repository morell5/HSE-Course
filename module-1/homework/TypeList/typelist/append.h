#pragma once

#include "typelist.h"

template<typename TList, typename NewType>
struct Append;

template<>
struct Append<NullType, NullType> {
    typedef NullType NewTypeList;
};

template<typename T>
struct Append<NullType, T> {
    typedef TypeList<T, NullType> NewTypeList;
};

template<typename Head, typename Tail>
struct Append<NullType, TypeList<Head, Tail>> {
    typedef TypeList<Head, Tail> NewTypeList;
};

template<typename Head, typename Tail, typename T>
struct Append<TypeList<Head, Tail>, T> {
    typedef TypeList<Head, typename Append<Tail, T>::NewTypeList> NewTypeList;
};