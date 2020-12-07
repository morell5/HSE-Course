#pragma once

#include "typelist.h"

template<typename TList, typename TargetType>
struct Erase;

template<typename L, typename El, typename Deaf>
struct Erase<TypeList<L, El>, Deaf>{
    using NewTypeList = TypeList<L, typename Erase<El, Deaf>::NewTypeList>;
};

template<typename Deaf>
struct Erase<NullType, Deaf>{
    using NewTypeList = NullType;
};

template<typename L, typename El>
struct Erase<TypeList<L, El>, L> {
  using NewTypeList = El;
};