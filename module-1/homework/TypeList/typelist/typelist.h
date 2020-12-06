#pragma once

template<typename H, typename T> 
struct TypeList {
	typedef H Head;
	typedef T Tail;
};

struct NullType {};