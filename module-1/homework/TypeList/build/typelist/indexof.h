#pragma once

#include "typelist.h"

template<typename TargetType>
struct IndexOf<NullType, TargetType>
{
	const static int pos = -1;
};

template<typename TList>
struct IndexOf<TList, typename TList::H>
{
	const static int pos = 0;
};

template<typename TList, typename TargetType>
struct IndexOf
{
private:
	const static int test_ind = IndexOf<typename TList::T, TargetType>::pos;
public:
	const static int pos = (test_ind == -1) ? -1 : test_ind + 1;
};


