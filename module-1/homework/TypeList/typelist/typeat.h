#pragma once

#include "typelist.h"

template<typename TList, unsigned int index>
struct TypeAt;

template<typename Head, typename Tail>
struct TypeAt<TypeList<Head, Tail>, 0> {
    typedef Head TargetType;
};

template<typename Head, typename Tail, unsigned int index>
struct TypeAt<TypeList<Head, Tail>, index>{
    typedef typename TypeAt<Tail, index - 1>::TargetType TargetType;
}
