#include <utility>

// args is not visible in function scope => we can not pass args to T
// but we NEED to call T with Args
// Solution: declval to the rescue
struct D {
    template<typename T, typename... Args, typename=decltype(T(std::declval<Args>()...))>
    static void foo(Args&&...) {
        decltype(T(std::declval<Args>()...)) x;
        x = 3;
    }
};

struct Base {
    template<typename... Args>
    Base(Args...) {};
};

int main() {
    D::foo<Base>(1, 2, 3);
    return 0;
}