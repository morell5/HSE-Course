#pragma once

#include "typelist.h"

template<typename TList> 
struct Length;

template<typename H, typename T>
struct Length<TypeList<H, T>> {
	enum {
		length = 1 + Length<T>::length
	};
};
template<>
struct Length<NullType> {
	enum {
		length = 0
	};
};