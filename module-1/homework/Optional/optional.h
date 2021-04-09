#include <cstdlib>
#include <type_traits>

#pragma once

namespace task {

struct NullOpt {
    // Your code goes here;
};

constexpr NullOpt kNullOpt = // Your code goes here;

struct InPlace {
    // Your code goes here;
};

constexpr InPlace kInPlace =  //Your code goes here;

template <typename T>
class Optional : public // Your code goes here; {
public:
    using value_type =  // Your code goes here;

    constexpr Optional() noexcept;

    template <typename U = value_type>
    constexpr explicit Optional(U&& value);

    constexpr explicit Optional(NullOpt) noexcept;

    template <typename... Args>
    constexpr explicit Optional(InPlace, Args&&... args);

    Optional& operator=(NullOpt) noexcept;

    template <typename U = T>
    Optional& operator=(U&& value);

    void Reset() noexcept;

    template <typename U>
    constexpr T ValueOr(U&& default_value) const&;

    template <typename U>
    constexpr T ValueOr(U&& default_value) &&;

    constexpr bool HasValue() const noexcept;

    constexpr explicit operator bool() const noexcept;

    constexpr std::add_pointer_t<const value_type> operator->() const;

    constexpr std::add_pointer_t<value_type> operator->();

    constexpr const value_type& operator*() const&;

    constexpr value_type& operator*() &;

    constexpr const value_type&& operator*() const&&;

    constexpr value_type&& operator*() &&;
};
}  // namespace task