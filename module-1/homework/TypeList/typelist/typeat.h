#pragma once

#include "typelist.h"

template<typename TList, unsigned int index>
struct TypeAt;

template<typename TList, unsigned int index>
struct TypeAt {
    using TargetType = typename TypeAt<typename TList::tail, index - 1>::TargetType;
};

template<typename TList>
struct TypeAt<TList, 0> {
    using TargetType = typename TList::head;
};