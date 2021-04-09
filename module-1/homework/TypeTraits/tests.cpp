#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>

#include "gtest/gtest.h"
#include "type_traits/is_copy_constructible.h"
#include "type_traits/is_nothrow_move_constructible.h"
#include "type_traits/move_if_noexcept.h"

TEST(IsConstructible, Test1) {

    class Foo {
    public:
        explicit Foo(int32_t n) : v1_(n), v2_() {
        }
        Foo(int32_t n, double f) noexcept : v1_(n), v2_(f) {
        }
        void Bar() {
            v1_ = 0;
            v2_ = 0;
        }

    private:
        int32_t v1_;
        double v2_;
    };

    static_assert(IsConstructible<Foo, int32_t>::value, "expected true");
}

TEST(IsConstructible, Test2) {

    static_assert(IsConstructible<int32_t, double>::value, "expected true");
}

TEST(IsConstructible, Test3) {

    struct Base {};

    struct Derived : Base {};

    static_assert(!IsConstructible<Derived, Base>::value, "expected false");

    static_assert(IsConstructible<Base, Derived>::value, "expected true");
}

TEST(IsConstructible, Test4) {

    struct Foo {};

    static_assert(!IsConstructible<Foo&, Foo>::value, "expected false");

    static_assert(IsConstructible<Foo&, Foo&>::value, "expected true");
    //IsConstructibleHelper::TestUnary<Foo&, Foo&>(0);
//    Foo f = Foo{};
//    IsConstructibleHelper::ImplicitCast<Foo&>(f);
//    std::cout << IsConstructibleHelper::TypeCast<Foo&, Foo&>().value;
    static_assert(!IsConstructible<Foo&, Foo&&>::value, "expected false");
}

TEST(IsConstructible, Test5) {

    struct Foo {};

    static_assert(IsConstructible<Foo&&, Foo>::value, "expected true");

    static_assert(!IsConstructible<Foo&&, Foo&>::value, "expected false");

    static_assert(IsConstructible<Foo&&, Foo&&>::value, "expected true");
}

TEST(IsConstructible, Test6) {

    struct Foo {};

    static_assert(IsConstructible<Foo, Foo>::value, "expected true");

    static_assert(IsConstructible<Foo, Foo&>::value, "expected true");

    static_assert(IsConstructible<Foo, Foo&&>::value, "expected true");
}

TEST(IsNoThrowMoveConstructible, Test1) {

    struct Foo {
        std::string str;
    };

    static_assert(IsNoThrowMoveConstructible<Foo>::value, "expected true");
}

TEST(IsNoThrowMoveConstructible, Test2) {

    struct Foo {
        Foo(Foo&&) = default;

        int32_t n;
    };

    static_assert(IsNoThrowMoveConstructible<Foo>::value, "expected true");
}

TEST(IsNoThrowMoveConstructible, Test3) {

    struct Foo {
        Foo(const Foo&) {
        }
    };

    static_assert(!IsNoThrowMoveConstructible<Foo>::value, "expected true");
}

TEST(MoveIfNoExcept, Test1) {

    struct ThrowFoo {
        bool copy = false;
        ThrowFoo() = default;
        ThrowFoo(ThrowFoo&&){};
        ThrowFoo(const ThrowFoo&) {
            copy = true;
        };
    };
    ThrowFoo foo;
    std::cout << foo.copy << '\n';
    ThrowFoo foo2 = MoveIfNoExcept(foo);
    std::cout << foo2.copy << '\n';
    std::cout << IsNoThrowMoveConstructible<ThrowFoo>::value;

    ASSERT_TRUE(foo2.copy);
}

TEST(MoveIfNoExcept, Test2) {

    struct NonThrowFoo {
        NonThrowFoo() = default;
        NonThrowFoo(NonThrowFoo&&) noexcept {};
        NonThrowFoo(const NonThrowFoo&) noexcept {
            copy = true;
        };

        bool copy = false;
    };
    NonThrowFoo foo;
    NonThrowFoo foo2 = MoveIfNoExcept(foo);
    ASSERT_FALSE(foo2.copy);
}