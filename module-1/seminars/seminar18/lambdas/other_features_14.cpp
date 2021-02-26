
void foo() {
    // C++20: 
    auto lam = [](int x) {return x + 1;};
    // lambda default constructible since C++20
    // decltype(lam) copy;

    // C++17: lambda constexpr by default
    static_assert(lam(42) == 43);
    static_assert(not noexcept(lam(42)));
}

int main() {
    
    return 0;
}