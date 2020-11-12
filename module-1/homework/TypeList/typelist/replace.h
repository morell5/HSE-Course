#pragma once

#include "typelist.h"

template<typename TList, typename OldType, typename NewType>
struct Replace;

template<typename OldType, typename NewType>
struct Replace<NullType, OldType, NewType> {
  using NewTypeList = NullType;
};

template<typename OldType, typename NewType, typename U>
struct Replace<TypeList<OldType, U>, OldType, NewType> {
  using NewTypeList = TypeList<NewType, U>;
};

template<typename OldType, typename NewType, typename T, typename U>
struct Replace<TypeList<T, U>, OldType, NewType> {
  using NewTypeList = TypeList<T, typename Replace<U, OldType, NewType>::NewTypeList>;
};