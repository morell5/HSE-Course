#pragma once

#include "erase.h"
#include "typelist.h"

template<typename TList>
struct NoDuplicates;

template<typename L, typename El>
struct NoDuplicates<TypeList<L, El>>{
    using NewTypeList = TypeList<L, typename EraseAll<typename NoDuplicates<El>::NewTypeList, L>::NewTypeList>;
};

template<>
struct NoDuplicates<NullType> {
  using NewTypeList = NullType;
};