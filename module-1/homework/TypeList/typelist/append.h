#pragma once

#include "typelist.h"

template<typename TList, typename NewType>
struct Append;

// [Null] & [Null]
template<>
struct Append<NullType, NullType> {
  using NewTypeList = NullType;
};

// [List] & [Null]
template<typename T, typename U>
struct Append<TypeList<T, U>, NullType> {
  using NewTypeList = TypeList<T, U>;
};

// [Head-only List] & [T]
template<typename Type, typename T>
struct Append<TypeList<T, NullType>, Type> {
  using NewTypeList = TypeList<T, TypeList<Type, NullType>>;
};

// [List] & [List]
template<typename T1, typename U1, typename T2, typename U2>
struct Append<TypeList<T1, U1>, TypeList<T2, U2>> {
private:
  using List = typename Append<TypeList<T1, U1>, T2>::NewTypeList;
public:
  using NewTypeList = typename Append<List, U2>::NewTypeList;
};

// [List] & [T]
template<typename T, typename U, typename Type>
struct Append<TypeList<T, U>, Type> {
  using NewTypeList = TypeList<T, typename Append<U, Type>::NewTypeList>;
};

// [Null] & [T]
template<typename Type>
struct Append<NullType, Type> {
  using NewTypeList = TypeList<Type, NullType>;
};