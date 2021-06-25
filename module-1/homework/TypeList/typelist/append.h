#pragma once

#include "typelist.h"

template<typename TList, typename NewType>
struct Append;

template<typename TList, typename NewType>
struct Append {
    using NewTypeList = TypeList<typename TList::Head, typename Append<typename TList::Tail, NewType>::NewTypeList>;
};

template<typename NewType>
struct Append<NullType, NewType> {
    using NewTypeList = TypeList<NewType, NullType>;
};

template<>
struct Append<NullType, NullType> {
    using NewTypeList = NullType;
};
