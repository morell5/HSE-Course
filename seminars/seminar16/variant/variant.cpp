#include <iostream>
#include <type_traits>
#include <utility>

//----------------Helper structures----------------

template <std::size_t I> struct in_place_index_t {
    explicit in_place_index_t() = default;
};

template <std::size_t I>
constexpr in_place_index_t<I> in_place_index{};


template<std::size_t _Index, typename... _Types>
union __union;

template<std::size_t _Index>
union  __union<_Index> {};

template<std::size_t _Index, typename T, typename... _Types> 
union __union<_Index, T, _Types...> {
    public:

    T head;
    __union<_Index + 1, _Types...> tail;

    friend struct __access_union;
};

struct __assign_union {
    template<std::size_t Idx, typename U, std::size_t UnIdx, typename Head, typename... Tail>
    static void assign_helper(U&& value,  in_place_index_t<0>, __union<UnIdx, Head, Tail...>& u) {
        u.head = value;
    }

    template<std::size_t Idx, typename U, std::size_t UnIdx, typename Head, typename... Tail>
    static void assign_helper(U&& value, in_place_index_t<Idx>,  __union<UnIdx, Head, Tail...>& u) {
        assign_helper<Idx - 1>(std::forward<U>(value), in_place_index<Idx - 1>, u.tail);
    }
};

struct __access_union {
    template<typename U>
    static constexpr auto&& __get_alt(U&& __v, in_place_index_t<0>) {
        return std::forward<U>(__v).__head;
    }

    
    template<typename U, std::size_t Idx>
    static constexpr auto&& __get_alt(U&& __v, in_place_index_t<Idx>) {
        return __get_alt(std::forward<U>(__v).__tail, in_place_index<Idx - 1>);
    }
};

struct __my_variant {
  template<std::size_t Idx, typename T>
  static constexpr auto&& __get_alt(T&& __v) {
    return __access_union::__get_alt(std::forward<T>(__v).__data, in_place_index<Idx>);
  }
};
//----------------Helper structures----------------


//----------------_find_exactly_one_t----------------
const static int not_founded = - 1;
const static int ambiguity = not_founded - 1;

constexpr std::size_t simplified_condition(std::size_t i, std::size_t res, bool founded_value) {
     return (!founded_value) ? res : ((res == not_founded) ? i : ambiguity);
}

template<std::size_t SizeofFounded>
constexpr std::size_t __check_dublicates__(std::size_t cur_pos, const bool (&founded)[SizeofFounded]) {
   return (cur_pos == SizeofFounded) ? not_founded :  simplified_condition(cur_pos, __check_dublicates__(cur_pos + 1, founded), founded[cur_pos]);
}

template<typename TargetType, typename... Types>
struct _find_exactly_one_checked_ {
    constexpr static bool founded[sizeof...(Types)] = {std::is_same<TargetType, Types>::value...}; 
    constexpr static std::size_t value = __check_dublicates__(0, founded);
};

template<typename T>
struct _find_exactly_one_checked_<T> {
    static_assert(!std::is_same<T, T>::value, "type not in empty type list");
};

template<typename TargetType, typename... Types>
struct _find_exactly_one_t : public _find_exactly_one_checked_<TargetType, Types...> {};
//----------------_find_exactly_one_t----------------


//----------------My variant----------------
template<typename... Types>
class my_variant {
    
    public:
    __union<0, Types...> __data;

    public:

    my_variant() = default;
    my_variant(Types... args)  {};
    my_variant& operator=(const my_variant& other) { return *this; }
    template<typename T, std::size_t Pos=_find_exactly_one_t<T, Types...>::value>
    my_variant& operator=(T&& value) { 
        __assign_union::assign_helper<Pos>(std::forward<T>(value), in_place_index<Pos>, __data);

        return *this; 
    }

    private:
    friend __my_variant;

};
//----------------My variant----------------


//----------------Variant alternative----------------
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

template <std::size_t I, typename... Types>
struct  variant_alternative;

template <std::size_t I, typename... Types>
struct variant_alternative<I, my_variant<Types...>> {
    using type = typename TypeAt<I, Typelist<Types...>>::Result;
};
template <std::size_t I, typename... Types>
using my_variant_alternative_t = typename variant_alternative<I, Types...>::type;
//----------------Variant alternative----------------

//----------------Getters----------------
template<std::size_t Idx, typename T>
auto&& generic_get(T&& v) {
    return __my_variant::__get_alt<Idx>(std::forward<T>(v))._value;
}

template<std::size_t Idx, typename... Types>
my_variant_alternative_t<Idx, my_variant<Types...>>& get(my_variant<Types...>& v) {
    return generic_get<Idx>(v);
}

template<typename T, typename... Types>
T& get(my_variant<Types...>& v) {
    return get<_find_exactly_one_t<Types...>::value>(v);
}

template<typename T, typename... Types>
T&& get(my_variant<Types...>&& v) {
    return get<_find_exactly_one_t<Types...>::value>(std::move(v));
}
//----------------Getters----------------

int main() {
        my_variant<const char*, int, double> v, w;
        v = 1000;
        
        std::cout << v.__data.tail.head;
        
        // we get a segfault
        // int i = get<int>(v);
        return 0;
}