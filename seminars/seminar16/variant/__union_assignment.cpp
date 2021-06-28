#include <iostream>
#include <string>
#include <type_traits>

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
    template<std::size_t Idx, typename U, std::size_t UnIdx, typename Head, typename... Tail>
    void assign_helper(U&& value,  in_place_index_t<0>, __union<UnIdx, Head, Tail...>& u) {
        u.head = value;
    }

    template<std::size_t Idx, typename U, std::size_t UnIdx, typename Head, typename... Tail>
    void assign_helper(U&& value, in_place_index_t<Idx>,  __union<UnIdx, Head, Tail...>& u) {
        assign_helper<Idx - 1>(std::forward<U>(value), in_place_index<Idx - 1>, u.tail);
    }

    template<std::size_t Idx, typename U>
    void assign(U&& value) {
        assign_helper<Idx>(std::forward<U>(value), in_place_index<Idx>, *this);
    }

    T head;
    __union<_Index + 1, _Types...> tail;

};
int main() {
    __union<0, const char*, int, float> u;
    u.assign<1>(1.2);
    std::cout << u.tail.head;
    return 0;
}