#pragma once

#include "typelist.h"

template <typename T>
struct Length {
    static const int length = 1;
};

template <typename ...T>
struct Length <TypeList<T...>> {
    static const int length = 1 + Length<typename TypeList<T...>::Tail>::length;
};

template <>
struct Length <NullType> {
    static const int length = 0;
};
