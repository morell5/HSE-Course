#include <algorithm>
#include <string>

#include "src/shared_ptr/shared_ptr.h"
#include <memory>

#include "gtest/gtest.h"

// weak_ptr
TEST(WeakExpired, Test1) {
    weak_ptr<int> w;
    {
        auto sp = make_shared<int>(42);
        w = sp;
        ASSERT_FALSE(w.expired());
    }
}

TEST(WeakExpired, Test2) {
    weak_ptr<int> w;
    {
        auto sp = make_shared<int>(42);
        w = sp;
    }
    ASSERT_TRUE(w.expired());
}

TEST(WeakReset, Test3) {
    weak_ptr<int> w;
    auto sp = make_shared<int>(42);
    w = sp;
    w.reset();
    ASSERT_TRUE(w.expired());
}

TEST(WeakLock, Test1) {
    weak_ptr<int> w;
    auto sp = make_shared<int>(42);
    w = sp;
    ASSERT_TRUE(*w.lock() == 42);
}

TEST(WeakLock, Test2) {
    weak_ptr<int> w;
    {
        auto sp = make_shared<int>(42);
        w = sp;
    }
    ASSERT_FALSE(w.lock());
}

// shared_ptr
TEST(SharedMoveConstructor, Test1) {
    class contrainer {};
    shared_ptr<contrainer> s1 = make_shared<contrainer>();
    contrainer* raw_s1 = s1.get();
    shared_ptr<contrainer> s2 = std::move(s1);
    ASSERT_TRUE(s1.use_count() == 0 && s1.get() == nullptr && s2.get() == raw_s1 && s2.use_count() == 1);
}

TEST(SharedMoveAssignment, Test1) {
    class contrainer {};
    shared_ptr<contrainer> s1 = make_shared<contrainer>();
    contrainer* raw_s1 = s1.get();
    shared_ptr<contrainer> s2;
    s2 = std::move(s1);
    ASSERT_EQ(s1.use_count(), 0);
    ASSERT_EQ(s1.get(), nullptr);
    ASSERT_EQ(s2.get(), raw_s1);
    ASSERT_EQ(s2.use_count(), 1);
    ASSERT_TRUE(s1.use_count() == 0 && s1.get() == nullptr && s2.get() == raw_s1 && s2.use_count() == 1);
}

TEST(SharedAssignment, Test1) {
    class contrainer {};
    shared_ptr<contrainer> s1 = make_shared<contrainer>();
    shared_ptr<contrainer> s2;
    shared_ptr<contrainer> s3;
    s2 = s1;
    s3 = s2;

    ASSERT_TRUE(s1.use_count() == 3 && s2.use_count() == 3 && s3.use_count() == 3 && s1.get() == s2.get() && s2.get() == s3.get());
}

TEST(SquareBracketsOperator, Test1) {
    shared_ptr<int[]> pis(new int[10]{0,1,2,3,4,5,6,7,8,9});
    pis[0] = 1;
    ASSERT_EQ(pis[0], 1);
}

TEST(SharedReset, Test1) {
    class contrainer {};
    shared_ptr<contrainer> s1 = make_shared<contrainer>();
    s1.reset();
    ASSERT_FALSE(s1);
}

TEST(SharedReset, Test2) {
    class contrainer {};
    shared_ptr<contrainer> s1 = make_shared<contrainer>();
    contrainer* p = new contrainer;
    s1.reset(p);

    ASSERT_TRUE(s1.get() == p && s1.use_count() == 1);
}

TEST(SharedReset, Test3) {
    class contrainer {};

    shared_ptr<contrainer> s1 = make_shared<contrainer>();
    contrainer* p = new contrainer;
    s1.reset(p, std::default_delete<contrainer>());

    ASSERT_TRUE(s1.get() == p && s1.use_count() == 1);
}

TEST(SharedUseCount, Test1) {
    class contrainer {};

    shared_ptr<contrainer> s1 = make_shared<contrainer>();
    shared_ptr<contrainer> s2 = s1;
    {
        shared_ptr<contrainer> s3 = s2;
    }

    ASSERT_TRUE(s1.use_count() == 2 && s2.use_count() == 2 && s1.get() == s2.get());
}

TEST(SharedSwap, Test1) {
    shared_ptr<int> s1 = make_shared<int>(1);
    shared_ptr<int> s2 = s1;
    shared_ptr<int> s3 = make_shared<int>(2);
    auto raw_s1 = s1.get();
    auto raw_s3 = s3.get();
    s1.swap(s3);

    ASSERT_TRUE(s1.use_count() == 1 && s2.use_count() == 2 && s3.use_count() == 2 && s2.get() == s3.get() && s2.get() == raw_s1 && s1.get() == raw_s3);
}

TEST(SharedIndirectionOperator, Test1) {
    shared_ptr<int> s1 = make_shared<int>(1);
    ASSERT_TRUE(*s1 == 1);
}

TEST(SharedArrowOperator, Test1) {
    struct contrainer {
        constexpr int foo() const noexcept { return 1; }
    };

    shared_ptr<contrainer> s1 = make_shared<contrainer>();
    ASSERT_TRUE(s1->foo() == 1);
}

TEST(SharedBoolOperator, Test1) {
    class contrainer {};

    shared_ptr<contrainer> s1 = make_shared<contrainer>();
    ASSERT_TRUE(s1);
}

TEST(SharedBoolOperator, Test2) {
    class contrainer {};

    shared_ptr<contrainer> s1;
    ASSERT_FALSE(s1);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}