#pragma once

#include "typelist.h"

template<typename TList, typename TargetType>
struct Erase;

template<typename TargetType>
struct Erase<NullType, TargetType> {
    typedef NullType NewTypeList;
};

template<typename TargetType, typename Tail>
struct Erase<TypeList<TargetType, Tail>, TargetType> {
    typedef Tail NewTypeList;
};

template<typename Head, typename Tail, typename TargetType>
struct Erase<TypeList<Head, Tail>, TargetType> {
    typedef TypeList<Head, typename Erase<Tail, TargetType>::NewTypeList> NewTypeList;
};