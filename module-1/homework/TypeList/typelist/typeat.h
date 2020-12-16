#pragma once

#include "typelist.h"

template<typename TList, unsigned int index>
struct TypeAt {
    typedef typename TypeAt<typename TList::T, index - 1>::TargetType TargetType;
};

template<typename TList>
struct TypeAt<TList, 0> {
    typedef typename TList::H TargetType;
};