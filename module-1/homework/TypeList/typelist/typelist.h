#pragma once

template<typename Head, typename Tail>
struct TypeList;

struct NullType {
};

template<typename Head, typename Tail>
struct TypeList {
    using head = Head;
    using tail = Tail;
};