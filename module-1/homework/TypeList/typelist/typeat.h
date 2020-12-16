#pragma once

#include "typelist.h"

template<typename TList, unsigned int index>
struct TypeAt;

template<typename L, typename El, unsigned int Nm>
struct TypeAt<TypeList<L, El>, Nm>
{
    using TargetType = typename TypeAt<El, Nm-1>::TargetType;
};

template<typename L, typename El>
struct TypeAt<TypeList<L, El>, 0>
{
    using TargetType = L;
};
