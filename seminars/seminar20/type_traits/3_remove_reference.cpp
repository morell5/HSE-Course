#include <type_traits>
#include <utility>

template <typename T>
struct RemoveReference {
    using Type = T;
};

template <typename T>
struct remove_reference<T&> {
    using Type = T;
};

template <typename T>
struct remove_reference<T&&> {
    using Type = T;
};

template <typename T>
using RemoveReferenceT = typename RemoveReference<T>::type;

int main() {
    static_assert(std::is_same<remove_reference_t<int&>, int>);
    static_assert(std::is_same<remove_reference_t<int>, int>);
    return 0;
}