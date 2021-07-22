#include <iostream>
#include <vector>

// Move Semantics Pitfalls
class A {
public:
    template<typename T>
    A(T&& t) : b_(std::move(t)) {}

private:
    B b_;
};

template<typename T>
class A {
public:
    A(T&& t) : b_(std::forward<T>(t)) {}

private:
    B b_;
};


class A {
public:
    template<typename T>
    A(T&& t) : 
        b_(std::forward<T>(t)),
        c_(std::forward<T>(t))
        {}

private:
    B b_;
    C c_;
};


class A {
public:
    template<typename T1, typename T2>
    A(T1&& t1, T2&& t2) : 
        b_(std::forward<T1>(t1)),
        c_(std::forward<T2>(t2))
        {}

private:
    B b_;
    C c_;
};

template<typename... Args>
std::unique_ptr<container> create(Args&&... args) {
    auto uptr( std::make_unique<Widget>(std::forward<Args>(args)...) );
    return std::move( uptr );
}


template<typename T>
void foo(T&&) {
    using NoRef = std::remove_reference_t<T>;
    if constexpr( std::is_integral_v<NoRef> ) {

    } else {

    }
}

