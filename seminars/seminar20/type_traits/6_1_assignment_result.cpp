#include <type_traits>
#include <utility>

template <typename T, typename U>
using assignment_result_t = decltype( std::declval<T>() = std::declval<U>() );

int main() {
    static_assert( std::is_same<assignment_result_t<int&, double>, int&>::value );
    // CE: ill-formed we can not assign int* to int&
    // assignment_result_t<int&, int*> x;
    // Next: what if the ill-formed expression is a = b?
    return 0;
}