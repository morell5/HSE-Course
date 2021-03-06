#include <cmath>
#include <string>

#include <optional>

#include "gtest/gtest.h"

TEST(ValueOR, Test1) {
  task::optional<std::string> opt("Hello world");
  ASSERT_EQ(opt.value_or("empty"), "Hello world");
}

TEST(ValueOR, Test2) {
  task::optional<std::string> opt;
  ASSERT_EQ(opt.value_or("empty"), "empty");
}

TEST(HasValue, Test1) {
    task::optional<std::string> opt("Hello world");
    ASSERT_TRUE(opt.has_value());
}

TEST(Reset, Test1) {
    task::optional<std::string> opt("Hello world");
    opt.reset();
    ASSERT_FALSE(opt.has_value());
}

TEST(ConversionToBool, Test1) {
    task::optional<std::string> opt("Hello world");
    ASSERT_TRUE(opt);
}

TEST(ArrowOperator, Test1) {
    task::optional<std::string> opt("Hello world");
    ASSERT_EQ(std::string(opt->c_str()), "Hello world");
}

TEST(IndirectionOperator, Test1) {
    task::optional<int> opt(1);
    ASSERT_EQ(*opt, 1);
}