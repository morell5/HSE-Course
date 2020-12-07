#pragma once

#include "typelist.h"
#include "append.h"

template<typename TList>
struct Reverse;

template<>
struct Reverse<NullType> {
    typedef NullType NewTypeList;
};

template<typename Head, typename Tail>
struct Reverse<TypeList<Head, Tail>> {
    typedef typename Append<
            typename Reverse<Tail>::NewTypeList, Head>::NewTypeList
        NewTypeList;
};
