#pragma once

#include "typelist.h"

template<typename TList, typename TargetType>
struct Count;

template<typename TargetType>
struct Count<NullType, TargetType> {
    enum { count = 0 };
};

template<typename Tail, typename TargetType>
struct Count<TypeList<TargetType, Tail>, TargetType> {
    enum { count = Count<Tail, TargetType>::count + 1 };
};

template<typename Head, typename Tail, typename TargetType>
struct Count<TypeList<Head, Tail>, TargetType> {
    enum { count = Count<Tail, TargetType>::count };
};
