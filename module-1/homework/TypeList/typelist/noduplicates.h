#pragma once

#include "erase.h"
#include "typelist.h"

template<typename TList>
struct NoDuplicates {
    using NewTypeList = TypeList<typename TList::Head,
            typename NoDuplicates<typename EraseAll<typename TList::Tail, typename TList::Head>::NewTypeList>::NewTypeList>;
};

template<>
struct NoDuplicates<NullType> {
    using NewTypeList = NullType;
};