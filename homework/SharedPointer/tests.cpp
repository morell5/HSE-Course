#include <algorithm>
#include <string>

#include "gtest/gtest.h"
#include "src/shared_ptr/shared_ptr.h"

// WeakPtr
TEST(WeakExpired, Test1) {
    WeakPtr<int32_t> w;
    {
        auto sp = MakeShared<int32_t>(42);
        w = sp;
        ASSERT_FALSE(w.Expired());
    }
}

TEST(WeakExpired, Test2) {
    WeakPtr<int32_t> w;
    {
        auto sp = MakeShared<int32_t>(42);
        w = sp;
    }
    ASSERT_TRUE(w.Expired());
}

TEST(WeakReset, Test3) {
    WeakPtr<int32_t> w;
    auto sp = MakeShared<int32_t>(42);
    w = sp;
    w.Reset();
    ASSERT_TRUE(w.Expired());
}

TEST(WeakLock, Test1) {
    WeakPtr<int32_t> w;
    auto sp = MakeShared<int32_t>(42);
    w = sp;
    ASSERT_TRUE(*w.Lock() == 42);
}

TEST(WeakLock, Test2) {
    WeakPtr<int32_t> w;
    {
        auto sp = MakeShared<int32_t>(42);
        w = sp;
    }
    ASSERT_FALSE(w.Lock());
}

// SharedPtr
TEST(SharedMoveConstructor, Test1) {
    class Contrainer {};
    SharedPtr<Contrainer> s1 = MakeShared<Contrainer>();
    Contrainer* raw_s1 = s1.Get();
    SharedPtr<Contrainer> s2 = std::move(s1);
    ASSERT_TRUE(s1.UseCount() == 0 && s1.Get() == nullptr && s2.Get() == raw_s1 &&
                s2.UseCount() == 1);
}

TEST(SharedMoveAssignment, Test1) {
    class Contrainer {};
    SharedPtr<Contrainer> s1 = MakeShared<Contrainer>();
    Contrainer* raw_s1 = s1.Get();
    SharedPtr<Contrainer> s2;
    s2 = std::move(s1);
    ASSERT_TRUE(s1.UseCount() == 0 && s1.Get() == nullptr && s2.Get() == raw_s1 &&
                s2.UseCount() == 1);
}

TEST(SharedAssignment, Test1) {
    class Contrainer {};
    SharedPtr<Contrainer> s1 = MakeShared<Contrainer>();
    SharedPtr<Contrainer> s2;
    SharedPtr<Contrainer> s3;
    s2 = s1;
    s3 = s2;

    ASSERT_TRUE(s1.UseCount() == 3 && s2.UseCount() == 3 && s3.UseCount() == 3 &&
                s1.Get() == s2.Get() && s2.Get() == s3.Get());
}

TEST(SharedReset, Test1) {
    class Contrainer {};
    SharedPtr<Contrainer> s1 = MakeShared<Contrainer>();
    s1.Reset();
    ASSERT_FALSE(s1);
}

TEST(SharedReset, Test2) {
    class Contrainer {};
    SharedPtr<Contrainer> s1 = MakeShared<Contrainer>();
    Contrainer* p = new Contrainer;
    s1.Reset(p);

    ASSERT_TRUE(s1.Get() == p && s1.UseCount() == 1);
}

TEST(SharedReset, Test3) {
    class Contrainer {};

    SharedPtr<Contrainer> s1 = MakeShared<Contrainer>();
    Contrainer* p = new Contrainer;
    s1.Reset(p, std::default_delete<Contrainer>());

    ASSERT_TRUE(s1.Get() == p && s1.UseCount() == 1);
}

TEST(SharedUseCount, Test1) {
    class Contrainer {};

    SharedPtr<Contrainer> s1 = MakeShared<Contrainer>();
    SharedPtr<Contrainer> s2 = s1;
    { SharedPtr<Contrainer> s3 = s2; }

    ASSERT_TRUE(s1.UseCount() == 2 && s2.UseCount() == 2 && s1.Get() == s2.Get());
}

TEST(SharedSwap, Test1) {
    SharedPtr<int> s1 = MakeShared<int32_t>(1);
    SharedPtr<int> s2 = s1;
    SharedPtr<int> s3 = MakeShared<int32_t>(2);
    auto raw_s1 = s1.Get();
    auto raw_s3 = s3.Get();
    s1.Swap(s3);

    ASSERT_TRUE(s1.UseCount() == 1 && s2.UseCount() == 2 && s3.UseCount() == 2 &&
                s2.Get() == s3.Get() && s2.Get() == raw_s1 && s1.Get() == raw_s3);
}

TEST(SharedIndirectionOperator, Test1) {
    SharedPtr<int> s1 = MakeShared<int32_t>(1);
    ASSERT_TRUE(*s1 == 1);
}

TEST(SharedArrowOperator, Test1) {
    struct Contrainer {
        constexpr int Foo() const noexcept {
            return 1;
        }
    };

    SharedPtr<Contrainer> s1 = MakeShared<Contrainer>();
    ASSERT_TRUE(s1->Foo() == 1);
}

TEST(SharedBoolOperator, Test1) {
    class Contrainer {};

    SharedPtr<Contrainer> s1 = MakeShared<Contrainer>();
    ASSERT_TRUE(s1);
}

TEST(SharedBoolOperator, Test2) {
    class Contrainer {};

    SharedPtr<Contrainer> s1;
    ASSERT_FALSE(s1);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}