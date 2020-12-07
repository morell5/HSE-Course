#pragma once

#include "typelist.h"

template<typename TList, typename TargetType>
struct IndexOf;

template<typename TargetType>
struct IndexOf<NullType, TargetType> {
    enum { pos = -1 };
};

template<typename Tail, typename TargetType>
struct IndexOf<TypeList<TargetType, Tail>, TargetType> {
    enum { pos = 0 };
};

template<typename Head, typename Tail, typename TargetType>
struct IndexOf<TypeList<Head, Tail>, TargetType> {
private:
    enum { tmp = IndexOf<Tail, TargetType>::pos };
public:
    enum { pos = tmp == -1 ? -1 : tmp + 1 };
};
