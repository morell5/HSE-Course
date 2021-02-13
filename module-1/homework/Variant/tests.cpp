#include <cmath>
#include <string>

#include "variant.h"

#include "gtest/gtest.h"

TEST(Get, Test1) {
    variant<int, double, std::string> v;
    v = "Hello world";
    ASSERT_EQ(std::get<std::string>(v),"Hello world");
}

TEST(Get, Test2) {
    variant<int, double, std::string> v;
    v = 12.0;
    ASSERT_NEAR(std::get<double>(v), 12.0, 1e-5);
}

TEST(Get, Test3) {
    variant<int, double, std::string> v;
    v = "Hello world";
    ASSERT_EQ(std::get<2>(v), "Hello world");
}

TEST(Get, Test4) {
    variant<int, double, std::string> v;
    v = 12.0;
    ASSERT_NEAR(std::get<1>(v), 12.0, 1e-5);
}