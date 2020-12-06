#pragma once

#include "typelist.h"

template<typename TList, typename OldType, typename NewType> 
struct Replace;

template<typename OldType, typename NewType>
struct Replace<NullType, OldType, NewType> {
	typedef NullType NewTypeList;
};

template<typename OldType, typename NewType, typename T>
struct Replace<TypeList<OldType, T>, OldType, NewType> {
	typedef TypeList<NewType, T> NewTypeList;
};

template<typename OldType, typename NewType, typename H, typename T>
struct Replace<TypeList<H, T>, OldType, NewType> {
	typedef TypeList<H, typename Replace<T, OldType, NewType>::NewTypeList> NewTypeList;
};