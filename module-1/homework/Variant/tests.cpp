#include <cmath>
#include <string>

#include "gtest/gtest.h"
#include "variant.h"

TEST(Get, Test1) {
    task::Variant<int32_t, double, std::string> v;
    v = "Hello world";
    ASSERT_EQ(Get<std::string>(v), "Hello world");
}

TEST(Get, Test2) {
    task::Variant<int32_t, double, std::string> v;
    v = 12.0;
    ASSERT_NEAR(Get<double>(v), 12.0, 1e-5);
}

TEST(Get, Test3) {
    task::Variant<int32_t, double, std::string> v;
    v = "Hello world";
    ASSERT_EQ(Get<2>(v), "Hello world");
}

TEST(Get, Test4) {
    task::Variant<int32_t, double, std::string> v;
    v = 12.0;
    ASSERT_NEAR(Get<1>(v), 12.0, 1e-5);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}