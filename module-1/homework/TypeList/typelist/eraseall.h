#pragma once

#include "typelist.h"

template<typename TList, typename TargetType>
struct EraseAll
{
	typedef TypeList<typename TList::H, typename EraseAll<typename TList::T, TargetType>::NewTypeList> NewTypeList;
};

template<typename TList>
struct EraseAll<TList, typename TList::H>
{
	typedef typename EraseAll<typename TList::T, typename TList::H>::NewTypeList NewTypeList;
};

template<typename TargetType>
struct EraseAll<NullType, TargetType>
{
	typedef NullType NewTypeList;
};
