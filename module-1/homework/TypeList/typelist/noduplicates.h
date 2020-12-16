#pragma once

#include "erase.h"
#include "typelist.h"

template<typename TList>
struct NoDuplicates {
    typedef TypeList<
            typename TList::H,
            typename NoDuplicates<
                    typename EraseAll<
                            typename TList::T,
                            typename TList::H
                    >::NewTypeList
            >::NewTypeList
    > NewTypeList;
};

template<>
struct NoDuplicates<NullType> {
    typedef NullType NewTypeList;
};