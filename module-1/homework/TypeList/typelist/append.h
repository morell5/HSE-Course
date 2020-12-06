#pragma once

#include "typelist.h"

template<typename TList, typename NewType>
struct Append;

template<> // Null & Null
struct Append<NullType, NullType> {
	typedef NullType NewTypeList;
};

template<typename H, typename T> // TypeList & Null
struct Append<TypeList<H, T>, NullType> {
	typedef TypeList<H, T> NewTypeList;
};

template<typename NewType> // Null & T
struct Append<NullType, NewType> {
	typedef TypeList<NewType, NullType> NewTypeList;
};

template<typename H, typename NewType> // HeadList & T
struct Append<TypeList<H, NullType>, NewType> {
	typedef TypeList<H, TypeList<NewType, NullType>> NewTypeList;
};

template<typename H1, typename T1, typename T> // TypeList & T
struct Append<TypeList<H1, T1>, T> {
	typedef Append<H1, typename Append<T1, T>::NewTypeList> NewTypeList;
};

template<typename H1, typename T1, typename H2, typename T2>  // TypeList & TypeList
struct Append<TypeList<H1, T1>, TypeList<H2, T2>> {
private:
	typedef typename Append<TypeList<H1, T1>, H2>::NewTypeList List;
public:
	typedef typename Append<List, T2>::NewTypeList NewTypeList;
};