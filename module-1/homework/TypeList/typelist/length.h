#pragma once

#include "typelist.h"

template<typename TList> 
struct Length;

template<> 
struct Length<NullType> {
    static constexpr size_t length = 0;
};

template<typename Head, typename Tail> 
struct Length<TypeList<Head, Tail>> {
    static constexpr size_t length = 1 + Length<Tail>::length;
};
