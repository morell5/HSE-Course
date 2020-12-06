#pragma once

#include "erase.h"
#include "typelist.h"

template<typename TList>
struct NoDuplicates;

template<>
struct NoDuplicates<NullType> {
	typedef NullType NewTypeList;
};

template<typename H, typename T>
struct NoDuplicates<TypeList<H, T>> {
private:
	typedef typename NoDuplicates<T>::NewTypeList NoDuplicatedTail;
	typedef typename Erase<NoDuplicatedTail, H>::NewTypeList UniqueTail;
public:
	typedef TypeList<H, UniqueTail> NewTypeList;
};