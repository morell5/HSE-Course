#include <cstdlib>
#include <utility>

#pragma once

namespace task {

template <typename... Types>
class Variant;

template <size_t Idx, typename T>
struct VariantAlternative;

template <size_t Idx, typename T>
using variant_alternative_t = typename VariantAlternative<Idx, T>::type;

template <size_t Idx, typename... Types>
struct VariantAlternative<Idx, Variant<Types...>> {
  using type =  // Your code goes here
};

template <typename... Types>
class Variant {
public:
    // Special member functions
    constexpr Variant() noexcept;

    template <typename T>
    Variant& operator=(T&& t) noexcept;

private:
    // Your code goes here
};

// Non-member functions
template <size_t I, typename... Types>
constexpr const variant_alternative_t<I, Variant<Types...>>& Get(Variant<Types...>& v);

template <size_t I, typename... Types>
constexpr variant_alternative_t<I, Variant<Types...>>&& Get(Variant<Types...>&& v);

template <typename T, typename... Types>
constexpr const T& Get(Variant<Types...>& v);

template <typename T, typename... Types>
constexpr T&& Get(Variant<Types...>&& v);

};  // namespace task