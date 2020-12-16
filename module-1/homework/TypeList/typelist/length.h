#pragma once

#include "typelist.h"

template<typename TList> 
struct Length;

template<typename L, typename El>
struct Length<TypeList<L, El>>
{
    enum{
        length = 1 + Length<El>::length
    };
};

template<typename L>
struct Length<TypeList<L, NullType>>
{
    enum{
        length = 1
    };
};

template<>
struct Length<NullType>
{
    enum{
        length = 0
    };
};
 