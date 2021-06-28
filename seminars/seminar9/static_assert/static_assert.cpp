#include <iostream>

template<std::size_t Size>
struct Fib {
    const static int val = Fib<Size - 1>::val + Fib<Size - 2>::val;
};

template<>
struct Fib<1> {
    const static int val = 1;
};

template<>
struct Fib<0> {
    const static int val = 1;
};

# define my_static_assert(expr) {char x[(expr) ? 1 : -1]; }

int main() {
    // раньше:
    my_static_assert(Fib<1>::val == 1);
    // сейчас:
    static_assert(Fib<1>::val == 1);
    return 0;
}