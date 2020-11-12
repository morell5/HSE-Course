#pragma once

#include "typelist.h"

template<typename TList, typename TargetType>
struct Erase;

template<typename Type>
struct Erase<NullType, Type> {
  using NewTypeList = NullType;
};

template<typename Type, typename U>
struct Erase<TypeList<Type, U>, Type> {
  using NewTypeList = U;
};

template<typename T, typename U, typename Type>
struct Erase<TypeList<T, U>, Type> {
  using NewTypeList = TypeList<T, typename Erase<U, Type>::NewTypeList>;
};