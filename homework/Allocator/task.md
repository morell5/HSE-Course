# Allocator

## Problem

Get your `list` implementation from the problem `List`

Add:
* move-constructor
* move-assignment operator
* iterator (it must admit `LegacyBidirectionalIterator`)
* allocator for `Node` type (it must admit [Allocator requirements](https://en.cppreference.com/w/cpp/named_req/Allocator))
    * you may choose on of [algorithms](https://github.com/mtrebi/memory-allocators)
    * `C++11` interface

Должно быть:
* `list.h` - interface and implementation from the `List` problem
* `allocator.h` - interface and implementation must admit `C++11` interface

Simplification: it's expected for the type template parameter `T` that

```c++
std::is_trivially_constructible<T>::value <- true
```