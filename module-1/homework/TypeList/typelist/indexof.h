#pragma once

#include "typelist.h"

template<typename TList, typename TargetType>
struct IndexOf;

template <typename T>
struct IndexOf<NullType, T> { // 404 not found :(
    static const int pos = -1;
};

template <typename TargetType, typename ...T>
struct IndexOf<TypeList<TargetType, T...>, TargetType> {
    static const int pos = 0;
};

template <typename ...T, typename TargetType>
struct IndexOf<TypeList<T...>, TargetType> {
private:
    static const int tmp = IndexOf<typename TypeList<T...>::Tail , TargetType>::pos;
public:
    static const int pos = tmp == -1 ? -1 : 1 + tmp;
};