#include <iostream>
#include <vector>

// для отсуттствующего типа, выводится -1

struct NullType {};

template<typename Head, typename Tail>
struct TypeList {
    typedef Head H;
    typedef Tail T;
};


template<typename TList, typename TargetType>
struct IndexOf;

template<typename TargetType>
struct IndexOf<NullType, TargetType> {
    const static int pos = -1;
};

template<typename Tail, typename TargetType>
struct IndexOf<TypeList<TargetType, Tail>, TargetType> {
    const static int pos = 0;
};

template<typename Head, typename Tail, typename TargetType>
struct IndexOf<TypeList<Head, Tail>, TargetType> {
    const static int pos = IndexOf<Tail, TargetType>::pos + 1;
};

int main() {
    typedef TypeList<int, NullType> tlist;
    
    std::cout << IndexOf<tlist, double>::pos;
    
    return 0;
}