#pragma once

#include "typelist.h"

template<typename TList, unsigned int index>
struct TypeAt;

template<typename T, typename U, unsigned int index>
struct TypeAt<TypeList<T, U>, index> {
  using Result = typename TypeAt<U, index - 1>::Result;
};

template<typename T, typename U>
struct TypeAt<TypeList<T, U>, 0> {
  using Result = T;
};