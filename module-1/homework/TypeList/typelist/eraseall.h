#pragma once

#include "typelist.h"

template<typename TList, typename TargetType>
struct EraseAll;

template<typename Type>
struct EraseAll<NullType, Type> {
  using NewTypeList = NullType;
};

template<typename Type, typename U>
struct EraseAll<TypeList<Type, U>, Type> {
  using NewTypeList = typename EraseAll<U, Type>::NewTypeList;
};

template<typename T, typename U, typename Type>
struct EraseAll<TypeList<T, U>, Type> {
  using NewTypeList = TypeList<T, typename EraseAll<U, Type>::NewTypeList>;
};