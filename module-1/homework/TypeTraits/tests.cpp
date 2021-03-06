#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>

#include "type_traits/is_copy_constructible.h"
#include "type_traits/is_nothrow_move_constructible.h"
#include "type_traits/move_if_noexcept.h"

#include "gtest/gtest.h"

TEST(is_constructible, Test1) {

    class Foo {
    private:
        int v1;
        double v2;
    public:
        Foo(int n) : v1(n), v2() {}
        Foo(int n, double f) noexcept : v1(n), v2(f) {}
    };

    static_assert(is_constructible<Foo, int>::value, "expected true");
}

TEST(is_constructible, Test2) {

    static_assert(is_constructible<int, double>::value, "expected true");
}

TEST(is_constructible, Test3) {
 
    struct Base {};

    struct Derived : Base {};

    static_assert(!is_constructible<Derived, Base>::value, "expected false");

    static_assert(is_constructible<Base, Derived>::value, "expected true");
}

TEST(is_constructible, Test4) {
 
    struct Foo {};

    static_assert(!is_constructible<Foo&, Foo>::value, "expected false");

    static_assert(is_constructible<Foo&, Foo&>::value, "expected true");

    static_assert(!is_constructible<Foo&, Foo&&>::value, "expected false");
}

TEST(is_constructible, Test5) {
 
    struct Foo {};

    static_assert(is_constructible<Foo&&, Foo>::value, "expected true");

    static_assert(!is_constructible<Foo&&, Foo&>::value, "expected false");

    static_assert(is_constructible<Foo&&, Foo&&>::value, "expected true");
}

TEST(is_constructible, Test6) {
 
    struct Foo {};

    static_assert(is_constructible<Foo, Foo>::value, "expected true");

    static_assert(is_constructible<Foo, Foo&>::value, "expected true");

    static_assert(is_constructible<Foo, Foo&&>::value, "expected true");
}

TEST(is_nothrow_move_constructible, Test1) {
 
    struct Foo {
        std::string str;
    };

    static_assert(is_nothrow_move_constructible<Foo>::value, "expected true");
}

TEST(is_nothrow_move_constructible, Test2) {
 
    struct Foo {
        int n;
        Foo(Foo&&) = default;
    };

    static_assert(is_nothrow_move_constructible<Foo>::value, "expected true");
}

TEST(is_nothrow_move_constructible, Test3) {
 
    struct Foo {
        Foo(const Foo&) {}
    };

    static_assert(!is_nothrow_move_constructible<Foo>::value, "expected true");
}

TEST(move_if_noexcept, Test1) {
    
    struct ThrowFoo {
        bool copy = false;
        ThrowFoo() = default;
        ThrowFoo(ThrowFoo&&) {};
        ThrowFoo(const ThrowFoo&) { copy = true; };
    };
    ThrowFoo foo;
    ThrowFoo foo2 = move_if_noexcept(foo); 
    ASSERT_TRUE(foo2.copy);
}

TEST(move_if_noexcept, Test2) {
 
    struct NonThrowFoo {
        bool copy = false;
        NonThrowFoo() = default;
        NonThrowFoo(NonThrowFoo&&) noexcept {};
        NonThrowFoo(const NonThrowFoo&) noexcept { copy = true; };
    };
    NonThrowFoo foo;
    NonThrowFoo foo2 = move_if_noexcept(foo); 
    ASSERT_FALSE(foo2.copy);
}