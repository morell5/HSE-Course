# TypeTraits

## Task

In this task you will implement the following type traits:
* [IsCopyConstructible](https://en.cppreference.com/w/cpp/types/is_copy_constructible)
* [IsNoThrowMoveConstructible](https://en.cppreference.com/w/cpp/types/is_move_constructible)
* [MoveIfNoExcept](https://en.cppreference.com/w/cpp/utility/move_if_noexcept)

The implementation in the corresponding header files:
* `is_copy_constructible.h`
* `is_nothrow_move_constructible.h`
* `move_if_noexcept.h`

You should use helper functions from `utility.h` 

Note: you may use following standardized type_traits
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