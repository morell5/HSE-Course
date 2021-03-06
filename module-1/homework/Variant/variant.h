#include <cstdlib>

#pragma once

namespace task {

template<typename... Types>
class variant;

template<std::size_t Idx, typename _Tp>
struct variant_alternative;

template<std::size_t Idx, typename T>
using variant_alternative_t = typename variant_alternative<Idx, T>::type;

template<std::size_t Idx, class... _Types>
struct variant_alternative<Idx, variant<_Types...>> {
  using type =  // Your code goes here
};

template<typename... Types>
class variant {

    public:
    
    // Special member functions
    constexpr variant() noexcept;
    
    template<typename T>
    variant& operator=( T&& t ) noexcept;
    
    private:
    // Your code goes here
};

// Non-member functions
template<std::size_t I, typename... Types>
constexpr variant_alternative_t<I, variant<Types...>>& get(variant<Types...>& v);

template<std::size_t I, typename... Types>
constexpr variant_alternative_t<I, variant<Types...>>&& get(variant<Types...>&& v);

template<typename T, typename... Types>
constexpr T& get(variant<Types...>& v);

template<typename T, typename... Types>
constexpr T&& get( variant<Types...>&& v );

};