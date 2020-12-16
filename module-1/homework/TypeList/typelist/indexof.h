#pragma once

#include "typelist.h"

template<typename TList, typename TargetType>
struct IndexOf;

template<typename TList, typename TargetType>
struct IndexOf {
    static const int pos = (IndexOf<typename TList::tail, TargetType>::pos) == -1
                           ? -1
                           : 1 + IndexOf<typename TList::tail, TargetType>::pos;
};

template<typename TargetType, typename Tail>
struct IndexOf<TypeList<TargetType, Tail>, TargetType> {
    static const int pos = 0;
};

template<typename TargetType>
struct IndexOf<NullType, TargetType> {
    static const int pos = -1;
};

