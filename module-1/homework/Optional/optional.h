#include <cstdlib>
#include <type_traits>

#pragma once

namespace task {

struct nullopt_t {
     // Your code goes here;
};

constexpr nullopt_t // Your code goes here;

struct in_place_t {
     // Your code goes here;
};

constexpr in_place_t  // Your code goes here;

template<typename T>
class optional {
    public:
    
        using value_type =  // Your code goes here;

        constexpr optional() noexcept;
        template < class U = value_type >
        constexpr optional( U&& value );
        constexpr optional(nullopt_t) noexcept;
        template<class... _Args>
        constexpr explicit optional(in_place_t, _Args&&... __args);
    
        template<typename U>
        constexpr T value_or(U&& default_value) const&;

        template<typename U>
        constexpr T value_or(U&& default_value) &&;

        constexpr bool has_value() const noexcept;

        constexpr explicit operator bool() const noexcept;

        constexpr std::add_pointer_t<const value_type> operator->() const;

        constexpr std::add_pointer_t<value_type> operator->();

        constexpr const value_type& operator*() const&;

        constexpr value_type& operator*() &;

        constexpr const value_type&& operator*() const&&;

        constexpr value_type&& operator*() &&;

    private:
      // Your code goes here;
};

};