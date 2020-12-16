#pragma once

#include "typelist.h"

template<typename TList>
struct Length;

template<typename TList>
struct Length {
    static const size_t length = 1 + Length<typename TList::tail>::length;
};

template<>
struct Length<NullType> {
    static const size_t length = 0;
};