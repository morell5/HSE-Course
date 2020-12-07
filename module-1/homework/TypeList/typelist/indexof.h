#pragma once

#include "typelist.h"

template<typename TList, typename TargetType>
struct IndexOf;

template<typename L, typename El, typename Deaf>
struct IndexOf<TypeList<L,El>, Deaf>{
    enum{
        pos1 = IndexOf<El, Deaf>::pos
    };
    enum{
        pos = (pos1 == -1) ? -1 : 1 + pos1
    };
};

template<typename Deaf>
struct IndexOf<NullType, Deaf> {
    enum{
        pos = -1
    };
};

template<typename L, typename Deaf>
struct IndexOf<TypeList<L, Deaf>, L> {
    enum{
        pos = 0
    };
};