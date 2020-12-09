#pragma once

#include "typelist.h"

template<typename TList, typename OldType, typename NewType> 
struct Replace;

template<typename OldType, typename NewType>
struct Replace<NullType, OldType, NewType> {
    typedef NullType NewTypeList;
};

template<typename OldType, typename Tail, typename NewType>
struct Replace<TypeList<OldType, Tail>, OldType, NewType> {
    typedef TypeList<NewType, Tail> NewTypeList;
};

template<typename Head, typename Tail, typename OldType, typename NewType>
struct Replace<TypeList<Head, Tail>, OldType, NewType> {
    typedef TypeList<Head, typename Replace<Tail, OldType, NewType>::NewTypeList> NewTypeList;
};