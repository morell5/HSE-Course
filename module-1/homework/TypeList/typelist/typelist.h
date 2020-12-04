#pragma once
#include <iostream>

// специализация по умолчанию
template<typename Head, typename Tail>
struct TypeList
{
	typedef Head H;
	typedef Tail T;
};

struct NullType {};



