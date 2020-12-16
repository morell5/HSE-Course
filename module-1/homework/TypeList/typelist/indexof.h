#pragma once

#include "typelist.h"

template<typename TList, typename TargetType>
struct IndexOf{
private:
    enum { temp = IndexOf<typename TList::T, TargetType>::pos };
public:
    enum { pos = temp == -1 ? -1 : temp + 1 };
};

template<typename TList>
struct IndexOf<TList, typename TList::H>{
    enum { pos = 0 };
};

template<typename TargetType>
struct IndexOf<NullType, TargetType> {
    enum { pos = -1 };
};