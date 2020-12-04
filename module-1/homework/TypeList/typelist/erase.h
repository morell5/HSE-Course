#pragma once

#include "typelist.h"

template<typename TList, typename TargetType>
struct Erase
{
	typedef TypeList<typename TList::H, typename Erase<typename TList::T, TargetType>::NewTypeList> NewTypeList;
};

template<typename TList>
struct Erase<TList, typename TList::H>
{
	typedef typename TList::T NewTypeList;
};

template<typename TargetType>
struct Erase<NullType, TargetType>
{
	typedef NullType NewTypeList;
};




