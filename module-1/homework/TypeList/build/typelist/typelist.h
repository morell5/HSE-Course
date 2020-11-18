#pragma once
#include <iostream>

template<typename Head, typename Tail>
struct TypeList
{
	typedef Head H;
	typedef Tail T;
};

struct NullType {};
