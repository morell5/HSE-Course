#pragma once

struct NullType {
};

template<typename head, typename tail>
struct TypeList {
    using Head = head;
    using Tail = tail;
};