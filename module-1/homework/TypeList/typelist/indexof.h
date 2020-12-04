#pragma once

#include "typelist.h"

template<typename TList, typename TargetType>
struct IndexOf
{
private:
	constexpr static int test_ind = IndexOf<typename TList::T, TargetType>::pos;
public:
	constexpr static int pos = (test_ind == -1) ? -1 : test_ind + 1;
};

template<typename TargetType>
struct IndexOf<NullType, TargetType>
{
	constexpr static int pos = -1;
};

template<typename TList>
struct IndexOf<TList, typename TList::H>
{
	constexpr static int pos = 0;
};



