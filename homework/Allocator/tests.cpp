#include <algorithm>
#include <list>
#include <random>
#include <string>

#include "gtest/gtest.h"
#include "src/allocator/allocator.h"
#include "src/list/list.h"

TEST(CopyAssignment, Test) {
    task::List<std::string, CustomAllocator<std::string>> actual;
    task::List<std::string, CustomAllocator<std::string>> actual_copy;
    std::list<std::string, CustomAllocator<std::string>> expected;
    std::list<std::string, CustomAllocator<std::string>> expected_copy;

    for (std::size_t i = 0; i < 10; i++) {
        actual_copy.PushBack("hello");
        expected_copy.push_back("hello");
    }

    actual = actual_copy;
    expected = expected_copy;
    ASSERT_TRUE(std::equal(actual.Begin(), actual.End(), expected.begin(), expected.end()));
}

TEST(MoveAssignment, Test1) {
    task::List<std::string> l1;
    task::List<std::string> l2;
    std::list<std::string> l3;
    std::list<std::string> l4;

    l1.PushBack("hello");
    l2 = std::move(l1);
    l3.push_back("hello");
    l4 = std::move(l3);

    ASSERT_TRUE(std::equal(l1.Begin(), l1.End(), l3.begin(), l3.end()));
    ASSERT_TRUE(std::equal(l2.Begin(), l2.End(), l4.begin(), l4.end()));
}

TEST(Front, Test1) {
    task::List<std::string, CustomAllocator<std::string>> actual;
    std::list<std::string, CustomAllocator<std::string>> expected;

    actual.PushBack("hello");
    expected.push_back("hello");

    actual.PushBack("hello");
    expected.push_back("hello");

    actual.PushBack("hello");
    expected.push_back("hello");

    actual.Clear();
    expected.clear();
    ASSERT_TRUE(std::equal(actual.Begin(), actual.End(), expected.begin(), expected.end()));
}

TEST(Clear, Test1) {
    task::List<std::string, CustomAllocator<std::string>> actual;
    std::list<std::string, CustomAllocator<std::string>> expected;

    for (std::size_t i = 0; i < 10; i++) {
        actual.PushBack("hello");
        expected.push_back("hello");
    }

    actual.Clear();
    expected.clear();
    ASSERT_TRUE(std::equal(actual.Begin(), actual.End(), expected.begin(), expected.end()));
}

TEST(Swap, Test1) {
    task::List<std::string, CustomAllocator<std::string>> actual;
    std::list<std::string, CustomAllocator<std::string>> expected;

    for (std::size_t i = 0; i < 10; i++) {
        actual.PushBack("hello");
        expected.push_back("hello");
    }

    task::List<std::string, CustomAllocator<std::string>> actual2;
    std::list<std::string, CustomAllocator<std::string>> expected2;

    for (std::size_t i = 0; i < 10; i++) {
        actual2.PushBack("world");
        expected2.push_back("world");
    }

    actual.Swap(actual2);
    expected.swap(expected2);
    ASSERT_TRUE(std::equal(actual.Begin(), actual.End(), expected.begin(), expected.end()));
    ASSERT_TRUE(std::equal(actual2.Begin(), actual2.End(), expected2.begin(), expected2.end()));
}

TEST(PushBack, Test) {
    std::vector<std::string> actual_v(10, "hello");
    std::vector<std::string> expected_v(10, "hello");
    task::List<std::string, CustomAllocator<std::string>> actual;
    std::list<std::string, CustomAllocator<std::string>> expected;

    for (std::size_t i = 0; i < 10; i++) {
        actual.PushBack(std::move(actual_v[i]));
        expected.push_back(std::move(expected_v[i]));
    }
    ASSERT_TRUE(std::equal(actual.Begin(), actual.End(), expected.begin(), expected.end()));
}

TEST(EmplaceBack, Test1) {
    task::List<std::string, CustomAllocator<std::string>> actual;
    std::list<std::string, CustomAllocator<std::string>> expected;

    for (std::size_t i = 0; i < 10; i++) {
        actual.EmplaceBack("hello");
        expected.emplace_back("hello");
    }
    ASSERT_TRUE(std::equal(actual.Begin(), actual.End(), expected.begin(), expected.end()));
}

TEST(PopBack, Test1) {
    task::List<std::string, CustomAllocator<std::string>> actual;
    std::list<std::string, CustomAllocator<std::string>> expected;

    for (std::size_t i = 0; i < 10; i++) {
        actual.EmplaceBack("hello");
        expected.emplace_back("hello");
    }

    for (std::size_t i = 0; i < 5; i++) {
        actual.PopBack();
        expected.pop_back();
    }
    ASSERT_TRUE(std::equal(actual.Begin(), actual.End(), expected.begin(), expected.end()));
}

TEST(PushFront, Test1) {
    std::vector<std::string> actual_v(10, "hello");
    std::vector<std::string> expected_v(10, "hello");
    task::List<std::string, CustomAllocator<std::string>> actual;
    std::list<std::string, CustomAllocator<std::string>> expected;

    for (std::size_t i = 0; i < 10; i++) {
        actual.PushFront(actual_v[i]);
        expected.push_front(expected_v[i]);
    }
    ASSERT_TRUE(std::equal(actual.Begin(), actual.End(), expected.begin(), expected.end()));
}

TEST(PushFront, Test2) {
    std::vector<std::string> actual_v(10, "hello");
    std::vector<std::string> expected_v(10, "hello");
    task::List<std::string, CustomAllocator<std::string>> actual;
    std::list<std::string, CustomAllocator<std::string>> expected;

    for (std::size_t i = 0; i < 10; i++) {
        actual.PushFront(std::move(actual_v[i]));
        expected.push_front(std::move(expected_v[i]));
    }
    ASSERT_TRUE(std::equal(actual.Begin(), actual.End(), expected.begin(), expected.end()));
}

TEST(EmplaceFront, Test1) {
    task::List<std::string, CustomAllocator<std::string>> actual;
    std::list<std::string, CustomAllocator<std::string>> expected;

    for (std::size_t i = 0; i < 10; i++) {
        actual.EmplaceFront("hello");
        expected.emplace_front("hello");
    }
    ASSERT_TRUE(std::equal(actual.Begin(), actual.End(), expected.begin(), expected.end()));
}

TEST(PopFront, Test1) {
    task::List<std::string, CustomAllocator<std::string>> actual;
    std::list<std::string, CustomAllocator<std::string>> expected;

    for (std::size_t i = 0; i < 10; i++) {
        actual.EmplaceBack("hello");
        expected.emplace_back("hello");
    }

    for (std::size_t i = 0; i < 5; i++) {
        actual.PopFront();
        expected.pop_front();
    }
    ASSERT_TRUE(std::equal(actual.Begin(), actual.End(), expected.begin(), expected.end()));
}

TEST(Resize, Test1) {
    task::List<std::string, CustomAllocator<std::string>> actual;
    actual.Resize(2);
    ASSERT_EQ(actual.Size(), 2);
}

TEST(Remove, Test1) {
    task::List<std::string, CustomAllocator<std::string>> actual;
    actual.PushBack("hello");
    actual.PushBack("world");
    actual.PushBack("hello");
    actual.Remove("hello");
    std::list<std::string, CustomAllocator<std::string>> expected;
    expected.push_back("world");
    ASSERT_TRUE(std::equal(actual.Begin(), actual.End(), expected.begin(), expected.end()));
}

TEST(Unique, Test1) {
    task::List<std::string, CustomAllocator<std::string>> actual;
    actual.PushBack("hello");
    actual.PushBack("hello");
    actual.PushBack("world");
    actual.PushBack("world");
    actual.Unique();
    std::list<std::string, CustomAllocator<std::string>> expected;
    expected.push_back("hello");
    expected.push_back("world");
    ASSERT_TRUE(std::equal(actual.Begin(), actual.End(), expected.begin(), expected.end()));
}

TEST(Sort, Test1) {
    std::random_device random_device;
    std::mt19937 random_engine(random_device());
    std::uniform_int_distribution<int> distribution(1, 100);

    task::List<int> actual;
    std::list<int> expected;
    for (size_t i = 0; i < 100; ++i) {
        int value = distribution(random_engine);
        actual.PushBack(value);
        expected.push_back(value);
    }
    actual.Sort();
    expected.sort();
    ASSERT_TRUE(std::equal(actual.Begin(), actual.End(), expected.begin(), expected.end()));
}

TEST(Mixed, Test1) {
    task::List<std::string, CustomAllocator<std::string>> actual;
    std::list<std::string, CustomAllocator<std::string>> expected;

    for (std::size_t i = 0; i < 5; i++) {
        actual.PushBack("hello");
        expected.push_back("hello");
    }

    for (std::size_t i = 0; i < 3; i++) {
        actual.PopFront();
        expected.pop_front();
    }

    for (std::size_t i = 0; i < 5; i++) {
        actual.PushFront("world");
        expected.push_front("world");
    }

    for (std::size_t i = 0; i < 3; i++) {
        actual.PopBack();
        expected.pop_back();
    }
    ASSERT_TRUE(std::equal(actual.Begin(), actual.End(), expected.begin(), expected.end()));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}