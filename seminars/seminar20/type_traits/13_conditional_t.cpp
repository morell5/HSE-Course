#include <type_traits>

template<bool B, typename T, typename F>
struct Conditional {
    using type = T;
};

template<typename T, typename F>
struct Conditional<false, T, F> {
    using type = F;
};

template<bool B, typename T, typename F>
using ConditionalT = typename Conditional<B, T, F>::type;

int main() {
    return 0;
}