#pragma once

#include "typelist.h"

template<typename TList> 
struct Length;

template<>
struct Length<NullType> {
    enum { length = 0 };
};

template<typename Head, typename Tail>
struct Length<TypeList<Head, Tail>> {
    enum { length = 1 + Length<Tail>::length };
};
