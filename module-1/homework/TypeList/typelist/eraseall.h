#pragma once

#include "typelist.h"

template<typename TList, typename TargetType>
struct EraseAll;

template<typename L, typename El, typename Deaf>
struct EraseAll<TypeList<L, El>, Deaf>{
    using NewTypeList = TypeList<L, typename EraseAll<El, Deaf>::NewTypeList>;
};

template<typename Deaf>
struct EraseAll<NullType, Deaf>{
    using NewTypeList = NullType;
};

template<typename L, typename Deaf>
struct EraseAll<TypeList<Deaf, L>, Deaf> {
  using NewTypeList = typename EraseAll<L, Deaf>::NewTypeList;
};