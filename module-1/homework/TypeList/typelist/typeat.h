#pragma once

#include "typelist.h"

template<typename TList, unsigned int index>
struct TypeAt;

template<typename H, typename T, unsigned int index>
struct TypeAt<TypeList<H, T>, index> {
	typedef typename TypeAt<T, index - 1>::TargetType TargetType;
};
template<typename H, typename T>
struct TypeAt<TypeList<H, T>, 0> {
	typedef H TargetType;
};
