# Allocator

## Задание

Взять свою имплементацию `list` из задания `List`

Добавить:
* move-constructor
* move-assignment operator
* iterator (должен удовлетворять категории `LegacyBidirectionalIterator`)
* allocator для `Node`
    * алгоритм размещения `Node` по алгоритму `StackAllocator`
    * интерфейс по `C++11`

Должно быть:
* `list.h` - интерфейс из задания `List`
* `list.cpp` - имплементация из задания `List`
* `allocator_11.h` - интерфейс аллокатора по `C++11`
* `allocator_11.cpp` - имплементация аллокатора по `C++11`

Упрощение: для шаблонного параметра `T` предполагается

```c++
std::is_trivially_constructible<T>::value <- true
```