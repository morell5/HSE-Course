#include <cmath>
#include <string>

#include "variant.h"

#include "gtest/gtest.h"

TEST(Get, Test1) {
    task::variant<int, double, std::string> v;
    v = "Hello world";
    ASSERT_EQ(get<std::string>(v),"Hello world");
}

TEST(Get, Test2) {
    task::variant<int, double, std::string> v;
    v = 12.0;
    ASSERT_NEAR(get<double>(v), 12.0, 1e-5);
}

TEST(Get, Test3) {
    task::variant<int, double, std::string> v;
    v = "Hello world";
    ASSERT_EQ(get<2>(v), "Hello world");
}

TEST(Get, Test4) {
    task::variant<int, double, std::string> v;
    v = 12.0;
    ASSERT_NEAR(get<1>(v), 12.0, 1e-5);
}