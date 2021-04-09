#include <iostream>
#include <concepts>
#include <vector>

template<class I>
concept forward_iterator =
    std::equality_comparable<I> && requires(I i) {
    typename std::incrementable_traits<I>::difference_type;
    typename std::indirectly_readable_traits<I>::value_type;
    typename std::common_reference_t<std::iter_reference_t<I>&&,
                                     typename std::indirectly_readable_traits<I>::value_type&>;
    *i++;
    typename std::common_reference_t<decltype(*i++)&&,
                                     typename std::indirectly_readable_traits<I>::value_type&>;
    requires std::signed_integral<typename std::incrementable_traits<I>::difference_type>;
  };

// It is more convenient to move forward_iterator to the template parameter list
template <forward_iterator Iter>
requires std::totally_ordered<Iter>
Iter MinElement(Iter first, Iter last) {
    if (first == last) {
        return first;
    }
    Iter min = first;
    while (++first != last) {
        if (*first < *min) {
            min = first;
        }
    }
    return min;
}

int main() {
    int32_t p[] = {10, 1, 2};
    std::vector<int32_t> v{10, -1, 2};
    // OK:
    std::cout << *MinElement(p, p+2) << std::endl;
    // OK:
    std::cout << *MinElement(v.begin(), v.end()) << std::endl;
    // CE: the required expression '*(i ++)' is invalid (i is an object of int)
    //std::cout << MinElement(1, 2) << std::endl;
    return 0;
}