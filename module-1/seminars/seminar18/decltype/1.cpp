#include <utility>

// args is visible in function scope => we can pass args to T (1)
struct D {
    template<typename T, typename... Args>
    static void foo(Args&&... args) {
        decltype(T(std::forward<Args>(args)...)) x;
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