#pragma once

#include "erase.h"
#include "typelist.h"

template<typename TList>
struct NoDuplicates;

template<>
struct NoDuplicates<NullType> {
  using NewTypeList = NullType;
};

template<typename T, typename U>
struct NoDuplicates<TypeList<T, U>> {
private:
  using Tail = typename NoDuplicates<U>::NewTypeList;
  using UniqueTail = typename EraseAll<Tail, T>::NewTypeList;
public:
  using NewTypeList = TypeList<T, UniqueTail>;
};
