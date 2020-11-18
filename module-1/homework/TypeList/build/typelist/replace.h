#pragma once

#include "typelist.h"

template<typename TList, typename OldType, typename NewType>
struct Replace
{
	typedef TypeList<typename TList::H, typename Replace<typename TList::T, OldType, NewType>::NewTypeList> NewTypeList;
};

template<typename OldType, typename NewType>
struct Replace<NullType, OldType, NewType>
{
	typedef NullType NewTypeList;
};

template<typename TList, typename NewType>
struct Replace<TList, typename TList::H, NewType>
{
	typedef TypeList<NewType, typename TList::T> NewTypeList;
};

