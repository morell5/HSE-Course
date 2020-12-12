#pragma once

#include "typelist.h"

template<typename TList>
struct Length {
    enum { length = 1 + Length<typename TList::T>::length };
};

template<>
struct Length<NullType> {
    enum { length = 0 };
};