#pragma once

template<typename H, typename T>
struct TypeList {
  using Head = H;
  using Tail = T;
};

struct NullType {
};