#pragma once

#include "typelist.h"

template<typename TList, typename NewType>
struct Append
{
	typedef TypeList<typename TList::H, Append<typename TList::T, NewType>> NewTypeList;
};

template<typename NewType>
struct Append<NullType, NewType>
{
	typedef TypeList<NewType, NullType> NewTypeList;
};
