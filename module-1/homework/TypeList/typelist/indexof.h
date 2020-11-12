#pragma once

#include "typelist.h"

template<typename TList, typename TargetType>
struct IndexOf;

template<typename Type>
struct IndexOf<NullType, Type> {
  enum {
    pos = -1
  };
};

template<typename U, typename Type>
struct IndexOf<TypeList<Type, U>, Type> {
  enum {
    pos = 0
  };
};

template<typename T, typename U, typename Type>
struct IndexOf<TypeList<T, U>, Type> {
private:
  enum {
    index = IndexOf<U, Type>::pos
  };
public:
  enum {
    pos = (index == -1) ? -1 : 1 + index
  };
};
