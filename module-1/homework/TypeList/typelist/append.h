#pragma once

#include "typelist.h"

template<typename TList, typename NewType>
struct Append;

template<>
struct Append<NullType, NullType> {
    typedef NullType NewTypeList;
};

template<typename Head, typename Tail>
struct Append<TypeList<Head, Tail>, NullType> {
    typedef TypeList<Head, Tail> NewTypeList;
};

template<typename NewType>
struct Append<NullType, NewType> {
    typedef TypeList<NewType, NullType> NewTypeList;
};

template<typename Head, typename Tail, typename NewType>
struct Append<TypeList<Head, Tail>, NewType> {
    typedef TypeList<Head,
            typename Append<Tail, NewType>::NewTypeList>
        NewTypeList;
};
