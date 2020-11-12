#pragma once

#include "typelist.h"

template<typename TList>
struct Length;

template<typename T, typename U>
struct Length<TypeList<T, U>> {
  enum {
    length = 1 + Length<U>::length
  };
};

template<>
struct Length<NullType> {
  enum {
    length = 0
  };
};
