#pragma once

#include "typelist.h"

// вычисление длины списка
template<typename TList>
struct Length
{
	static int constexpr length = 1 + Length<typename TList::T>::length;
};

template<>
struct Length<NullType>
{
	static int constexpr length = 0;
};
