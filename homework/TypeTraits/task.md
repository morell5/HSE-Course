# TypeTraits

## Задание

Реализовать:
* [IsCopyConstructible](https://en.cppreference.com/w/cpp/types/is_copy_constructible)
* [IsNoThrowMoveConstructible](https://en.cppreference.com/w/cpp/types/is_move_constructible)
* [MoveIfNoExcept](https://en.cppreference.com/w/cpp/utility/move_if_noexcept)

Реализация в соответсвующих header файлах

При реализации использовать хелперы из `utility.h` 

Замечание: следующие type_traits можно брать из std
* `std::negation`
* `std::is_base_of`
* `std::is_reference`
* `std::disjunction`
* `std::is_same`
* `std::false_type`
* `std::true_type`
* `std::integral_constant`
* `std::is_destructible`
* `std::conjunction`