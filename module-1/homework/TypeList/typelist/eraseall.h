#pragma once

#include "typelist.h"

template<typename TList, typename TargetType>
struct EraseAll;

template<typename TList, typename TargetType>
struct EraseAll {
    using NewTypeList = TypeList<typename TList::head, typename EraseAll<typename TList::tail, TargetType>::NewTypeList>;
};

template<typename TargetType, typename Tail>
struct EraseAll<TypeList<TargetType, Tail>, TargetType> {
    using NewTypeList = typename EraseAll<Tail, TargetType>::NewTypeList;
};

template<typename TargetType>
struct EraseAll<NullType, TargetType> {
    using NewTypeList = NullType;
};