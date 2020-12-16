#pragma once

#include "erase.h"
#include "typelist.h"

template<typename TList>
struct NoDuplicates;

template<typename TList>
struct NoDuplicates {
    using NewTypeList = TypeList<typename TList::head,
            typename NoDuplicates<typename EraseAll<typename TList::tail, typename TList::head>::NewTypeList>::NewTypeList>;
};

template<>
struct NoDuplicates<NullType> {
    using NewTypeList = NullType;
};