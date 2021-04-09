#include <cstdint>
#include <string>

#include "gtest/gtest.h"
#include "optional.h"

TEST(ValueOR, Test1) {
    task::Optional<std::string> opt("Hello world");
    ASSERT_EQ(opt.ValueOr("empty"), "Hello world");
}

TEST(ValueOR, Test2) {
    task::Optional<std::string> opt;
    ASSERT_EQ(opt.ValueOr("empty"), "empty");
}

TEST(HasValue, Test1) {
    task::Optional<std::string> opt("Hello world");
    ASSERT_TRUE(opt.HasValue());
}

TEST(Reset, Test1) {
    task::Optional<std::string> opt("Hello world");
    opt.Reset();
    ASSERT_FALSE(opt.HasValue());
}

TEST(ConversionToBool, Test1) {
    task::Optional<std::string> opt("Hello world");
    ASSERT_TRUE(opt);
}

TEST(ArrowOperator, Test1) {
    task::Optional<std::string> opt("Hello world");
    ASSERT_EQ(std::string(opt->c_str()), "Hello world");
}

TEST(IndirectionOperator, Test1) {
    task::Optional<int32_t> opt(1);
    ASSERT_EQ(*opt, 1);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}