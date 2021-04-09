#include <type_traits>
#include <utility>

template <typename T>
struct IsReference : std::false_type {};

template <typename T>
struct IsReference<T&> : std::true_type {};

template <typename T>
struct IsReference<T&&> : std::true_type {};

template <typename T>
inline constexpr bool kIsReferenceV = typename IsReference<T>::value;

int main() {
    static_assert(kIsReferenceV<int&>);
    static_assert(!kIsReferenceV<int>);
    return 0;
}