#include <cstdlib>
#include <utility>

#pragma once

template<class From, class To>
auto test_implicitly_convertible(int) -> decltype(
    void(std::declval<void(&)(To)>()(std::declval<From>())), std::true_type{}
);

template<class, class>
auto test_implicitly_convertible(...) -> std::false_type;

template<class From, class To>
struct is_implicitly_convertible : std::integral_constant<bool,
        decltype(test_implicitly_convertible<From, To>(0))::value> {};

template<std::size_t Index, typename... Types>
union __union;

template<std::size_t Index>
union  __union<Index> {

};

struct __union_helper {
    template<typename U>
    static constexpr auto&& get(U&& v, std::in_place_index_t<0>) {
        return std::forward<U>(v).head;
    }

    template<typename U, std::size_t Idx>
    static constexpr auto&& get(U&& v, std::in_place_index_t<Idx>) {
        return get(std::forward<U>(v).tail, std::in_place_index<Idx - 1>);
    }

    template<std::size_t Idx, typename U, std::size_t UnIdx, typename Head, typename... Tail>
    static void set(U&& value, std::in_place_index_t<0>, __union<UnIdx, Head, Tail...>& u) {
        if (std::is_same_v<Head, U>) {
            u.head = value;
        } else if (is_implicitly_convertible<U, Head>::value) {
            u.head = value;
        }
    }

    template<std::size_t Idx, typename U, std::size_t UnIdx, typename Head, typename... Tail>
    static void set(U&& value, std::in_place_index_t<Idx>, __union<UnIdx, Head, Tail...>& u) {
        set<Idx - 1>(std::forward<U>(value), std::in_place_index<Idx - 1>, u.tail);
    }
};


template<std::size_t Index, typename T, typename... Types>
union __union<Index, T, Types...> {
public:

    T head;
    __union<Index + 1, Types...> tail;

    __union() {
        if (!std::is_trivially_constructible_v<T>) {
            head = T();
        }
    }

    ~__union() {
        if (!std::is_trivially_destructible_v<T>) {
            head.~T();
        }
    }

    friend struct __union_helper;
};

template<typename... Types>
class variant;

template<std::size_t Idx, typename _Tp>
struct variant_alternative;

template<std::size_t Idx, typename T>
using variant_alternative_t = typename variant_alternative<Idx, T>::type;

static constexpr int not_founded = -1;


template<std::size_t SizeofFounded>
constexpr std::size_t find_type_pos(
        std::size_t cur_pos,
        const bool (&founded)[SizeofFounded],
        const bool (&constr)[SizeofFounded]
        ) {
    return (cur_pos == SizeofFounded) ? not_founded :
    ((founded[cur_pos] || constr[cur_pos]) ? cur_pos : find_type_pos(cur_pos + 1, founded, constr));
}

template<std::size_t SizeofFounded>
constexpr std::size_t find_type_pos(
        std::size_t cur_pos,
        const bool (&founded)[SizeofFounded]
) {
    return (cur_pos == SizeofFounded) ? not_founded :
           ((founded[cur_pos]) ? cur_pos : find_type_pos(cur_pos + 1, founded));
}

template<typename TargetType, typename... Types>
struct find_exactly_one_checked_ {
    constexpr static bool founded[sizeof...(Types)] = {std::is_same<TargetType, Types>::value...};
    constexpr static bool constructible[sizeof...(Types)] = {is_implicitly_convertible<TargetType, Types>::value...};
    constexpr static std::size_t valueForAssignment = find_type_pos(0, founded) == -1 ? find_type_pos(0, founded, constructible) : find_type_pos(0, founded);//find_type_pos(0, founded);
    constexpr static std::size_t value = find_type_pos(0, founded);//find_type_pos(0, founded);
};

template<typename TargetType, typename... Types>
struct find_exactly_one_t : public find_exactly_one_checked_<TargetType, Types...> {};

template<typename head, typename... tail>
struct Typelist{
    typedef head Head;
    typedef Typelist<tail...> Tail;
};

template<unsigned int index, class TList> struct TypeAt;

template<typename Head, typename... Tail>
struct TypeAt<0, Typelist<Head, Tail...>> {
    typedef Head Result;
};
template<unsigned int i, typename Head, typename... Tail>
struct TypeAt<i, Typelist<Head, Tail...>> {
    typedef typename TypeAt<i - 1, Typelist<Tail...>>::Result Result;
};

template<std::size_t Idx, class... Types>
struct variant_alternative<Idx, variant<Types...>> {
  using type = typename TypeAt<Idx, Typelist<Types...>>::Result;// Your code goes here
};


template<typename T, typename... Types>
auto&& generic_get(variant<Types...>& v) {
    return __union_helper::get(std::forward<variant<Types...>>(v).data_, std::in_place_index<find_exactly_one_t<T, Types...>::value>);
}

template<typename... Types>
class variant {
public:
    
    // Special member functions
    constexpr variant() noexcept;
    
    template<typename T>
    variant& operator=( T&& t ) noexcept;

    template<typename T, typename... Types_> friend
    auto&& generic_get(variant<Types_...>& v);
private:
    // Your code goes here
    __union<0, Types...> data_;
};

template<typename... Types>
template<typename T>
variant<Types...>& variant<Types...>::operator=(T&& t) noexcept {
    constexpr auto value = find_exactly_one_t<T, Types...>::valueForAssignment;
    static_assert(value != -1);
    __union_helper::set<value>(std::forward<T>(t), std::in_place_index<value>, this->data_);
    return *this;
}

template<typename... Types>
constexpr variant<Types...>::variant() noexcept {};


// Non-member functions
template<std::size_t I, typename... Types>
constexpr const variant_alternative_t<I, variant<Types...>>& get(variant<Types...>& v) {
    return generic_get<typename TypeAt<I, Typelist<Types...>>::Result>(std::forward<decltype(v)>(v));
}

template<std::size_t I, typename... Types>
constexpr variant_alternative_t<I, variant<Types...>>&& get(variant<Types...>&& v) {
    return generic_get<typename TypeAt<I, Typelist<Types...>>::Result>(std::move(v));
}

template<typename T, typename... Types>
constexpr const T& get(variant<Types...>& v) {
    return generic_get<T>(v);
}

template<typename T, typename... Types>
constexpr T&& get( variant<Types...>&& v ) {
    return generic_get<T>(std::move(v));
}
