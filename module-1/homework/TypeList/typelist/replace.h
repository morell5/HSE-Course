#pragma once

#include "typelist.h"

template<typename TList, typename OldType, typename NewType> 
struct Replace;

template<typename El, typename ot, typename nt>
struct Replace<TypeList<ot, El>, ot, nt>{
    using NewTypeList = TypeList<nt, typename Replace<El, ot, nt>::NewTypeList>;
};

template<typename L, typename El, typename ot, typename nt>
struct Replace<TypeList<L, El>, ot, nt>{
    using NewTypeList = TypeList<L, typename Replace<El, ot, nt>::NewTypeList>;
};

template<typename ot, typename nt>
struct Replace<NullType, ot, nt>{
    using NewTypeList = NullType;
};