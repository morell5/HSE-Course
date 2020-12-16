#pragma once

#include "typelist.h"

template<typename TList, typename NewType>
struct Append {
    typedef TypeList<
            typename TList::H,
            typename Append<typename TList::T, NewType>::NewTypeList
    > NewTypeList;
};

template<typename NewType>
struct Append<NullType, NewType> {
    typedef TypeList<NewType, NullType> NewTypeList;
};

template<>
struct Append<NullType, NullType> {
    typedef NullType NewTypeList;
};