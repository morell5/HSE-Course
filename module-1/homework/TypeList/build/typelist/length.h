#pragma once

#include "typelist.h"

// вычисление длины списка
template<typename TList>
struct Length
{
	static int const lenght = 1 + Length<typename TList::T>::lenght;
};

template<>
struct Length<NullType>
{
	static int const lenght = 0;
};
