#include <iostream>


// F.4: If a function might have to be evaluated at compile time, declare it constexpr  

constexpr int32_t Fac(int32_t n) {
    int32_t x = 1;
    for (int32_t i = 2; i <= n; ++i) {
        x *= i;
    }
    return x;
}

constexpr int32_t Min(int32_t x, int32_t y) { return x < y ? x : y; }

void Test(int32_t v) {
    int32_t m1 = Min(-1, 2);            // probably compile-time evaluation
    constexpr int32_t m2 = Min(-1, 2);  // compile-time evaluation
    int32_t m3 = Min(-1, v);            // run-time evaluation
    constexpr int32_t m4 = Min(-1, v);  // error: cannot evaluate at compile time
}

int main() {
    Test();
    return 0;
}
