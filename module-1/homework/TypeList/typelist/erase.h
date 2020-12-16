#pragma once

#include "typelist.h"

template<typename TList, typename TargetType>
struct Erase;

template<typename TList, typename TargetType>
struct Erase {
    using NewTypeList = TypeList<typename TList::head, typename Erase<typename TList::tail, TargetType>::NewTypeList>;
};

template<typename TargetType, typename Tail>
struct Erase<TypeList<TargetType, Tail>, TargetType> {
    using NewTypeList = Tail;
};

template<typename TargetType>
struct Erase<NullType, TargetType> {
    using NewTypeList = NullType;
};