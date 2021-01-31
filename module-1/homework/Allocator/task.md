# Allocator

## Задание

Взять свою имплементацию `list` из задания `List`

Добавить:
* move-constructor
* move-assignment operator
* iterator (должен удовлетворять категории `LegacyBidirectionalIterator`)
* allocator для `Node`(должен удовлетворять [Allocator requirements](https://en.cppreference.com/w/cpp/named_req/Allocator))
    * алгоритм размещения `Node` по одному из [алгоритмов](https://github.com/mtrebi/memory-allocators)
    * интерфейс по `C++11`

Должно быть:
* `list.h` - интерфейс и имплементация из задания `List`
* `allocator.h` - интерфейс и имплементация аллокатора по `C++11`

Упрощение: для шаблонного параметра `T` предполагается

```c++
std::is_trivially_constructible<T>::value <- true
```