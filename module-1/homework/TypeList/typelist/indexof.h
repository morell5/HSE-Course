#pragma once

#include "typelist.h"

template<typename TList, typename TargetType>
struct IndexOf;

template<typename TargetType>
struct IndexOf<NullType, TargetType> {
	enum {
		pos = -1
	};
};
template<typename T, typename TargetType>
struct IndexOf<TypeList<TargetType, T>, TargetType> {
	enum {
		pos = 0
	};
};
template<typename H, typename T, typename TargetType>
struct IndexOf<TypeList<H, T>, TargetType> {
private:
	enum {
		id = IndexOf<T, TargetType>::pos
	};
public:
	enum {
		pos = (id == -1) ? -1 : 1 + id
	};
};