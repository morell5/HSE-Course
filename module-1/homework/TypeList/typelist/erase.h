#pragma once

#include "typelist.h"

template<typename TList, typename TargetType>
struct Erase;

template<typename TargetType>
struct Erase<NullType, TargetType> {
	typedef NullType NewTypeList;
};

template<typename T, typename TargetType>
struct Erase<TypeList<TargetType, T>, TargetType> {
	typedef T NewTypeList;
};

template<typename H, typename T, typename TargetType>
struct Erase<TypeList<H, T>, TargetType> {
	typedef TypeList<H, typename Erase<T, TargetType>::NewTypeList> NewTypeList;
};