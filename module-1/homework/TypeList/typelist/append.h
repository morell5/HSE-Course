#pragma once

#include "typelist.h"

template<typename TList, typename NewType>
struct Append;

template<typename L, typename El, typename Newt>
struct Append<TypeList<L, El>, Newt>{
    using NewTypeList = TypeList<L, typename Append<El, Newt>::NewTypeList>;
};

template<typename L, typename Newt>
struct Append<TypeList<L, NullType>, Newt>{
    using NewTypeList = TypeList<L, TypeList<Newt, NullType>>;
};

template<typename Newt>
struct Append<TypeList<Newt, NullType>, NullType>{
    using NewTypeList = TypeList<Newt, NullType>;
};

template<typename Newt>
struct Append<NullType, Newt>{
    using NewTypeList = TypeList<Newt, NullType>;
};

template<>
struct Append<NullType, NullType>{
    using NewTypeList = NullType;
};