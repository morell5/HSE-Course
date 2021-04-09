#include <type_traits>
#include <utility>

template <typename T, typename Enable>
struct ALR_impl {
    using type = T;
};

template <typename T> 
// we put std::remove_reference_t<T&> here to triggere sfinae on
// std::remove_reference_t<void&> - because it causes CE
struct ALR_impl<T, std::remove_reference_t<T&>> {
    using type = T&;
};

template <typename T>
struct add_lvalue_reference : ALR_impl<T, std::remove_reference_t<T>> {};

int main() {
    
    // Notice that:
    // - we use partial spec => std::remove_reference_t<T&> == std::remove_reference_t<T> (same type)
    // - we don't user patial spec => std::remove_reference_t<T&> is ill-formed
    return 0; 
}