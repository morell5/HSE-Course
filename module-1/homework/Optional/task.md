# Optional

## Задание

[`Optional`](https://en.cppreference.com/w/cpp/utility/optional) - контейнер, реализующий функциональность опионального хранения</br> заданного значения / пустого значения (отдельно выделенного)

Конструкторы:

````c++
constexpr Optional() noexcept;
````

```c++
template< class U = value_type >
constexpr Optional( U&& value );  
```
        
```c++
constexpr Optional(nullopt_t) noexcept;
```

```c++
template<class... _Args>
constexpr explicit Optional(in_place_t, _Args&&... __args);
```

Реализовать операторы:
* `->` - разыменования с обращением к полю / методу 
* `*` - разыменования
* `bool()` - преобразование к `bool`

Методы:
* `HasValue` - проверка наличия значения
* `ValueOr` - возвращает хранимое значение при его наличии или передаваемый аргумент</br>
при отсутствии хранимого значения
* `Reset` - вызов деструктора у хранимого значении при наличии деструктора у типа этого значения

Можно использовать:
* `std::is_trivially_destructible`
* `std::addressof`
* `std::add_pointer_t`