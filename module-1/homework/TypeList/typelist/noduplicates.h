#pragma once

#include "erase.h"
#include "typelist.h"

template<typename TList>
struct NoDuplicates;

template<>
struct NoDuplicates<NullType> {
    typedef NullType NewTypeList;
};

template<typename Head, typename Tail>
struct NoDuplicates<TypeList<Head, Tail>> {
private:
    typedef typename Erase<Tail, Head>::NewTypeList tmp;
public:
    typedef TypeList<Head,
            typename NoDuplicates<tmp>::NewTypeList>
        NewTypeList;
};
