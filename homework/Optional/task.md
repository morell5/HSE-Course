# Optional

## Task

In this task you will implement the [`std::optional`](https://en.cppreference.com/w/cpp/utility/optional) class.</br>
Optional is a class that provides functionality of an optional storage</br>
 of the given value / default value

Constructors:

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

You should implement the following operations:
* `->` - arrow 
* `*` - indirection
* `bool()` - conversion to `bool`

Methods:
* `HasValue` - checking the presence of the value
* `ValueOr` -  returns stored value if it exists otherwise returns the argument</br>
* `Reset` - calls destructor of the stoed value if the type has the destructor

You can use:
* `std::is_trivially_destructible`
* `std::addressof`
* `std::add_pointer_t`