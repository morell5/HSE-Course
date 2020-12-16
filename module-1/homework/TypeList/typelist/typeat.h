#pragma once

#include "typelist.h"

template<typename TList, unsigned int index>
struct TypeAt;

template <typename ...T, unsigned int index>

struct TypeAt<TypeList<T...>, index> {
    typedef typename TypeAt<typename TypeList<T...>::Tail, index - 1>::TargetType TargetType;
};

template <typename ...T>
struct TypeAt<TypeList<T...>, 0> {
    typedef typename TypeList<T...>::Head TargetType;
};
