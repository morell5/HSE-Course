#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>
#include <vector>

#include "biginteger.h"
#include "gtest/gtest.h"

using namespace bulumutka;

#define SUM_TEST(a, b) { \
    BigInteger first = a; \
    BigInteger second = b; \
    BigInteger expected = a + b; \
    ASSERT_EQ(expected, first + second); \
} 

#define SUB_TEST(first, second) { \
    BigInteger a = first; \
    BigInteger b = second; \
    BigInteger expected = a - b; \
    ASSERT_EQ(expected, a - b); \
} 

TEST(Less, Test1) {
    BigInteger a = 10;
    BigInteger b = 5;
    BigInteger c = -5;
    BigInteger d = -10;

    ASSERT_TRUE(b < a);
    ASSERT_TRUE(c < b);
    ASSERT_TRUE(d < c);

    BigInteger a1("1000000000000000000000");
    BigInteger b1("1000000000000000000");
    ASSERT_TRUE(b1 < a1);
}

TEST(Equals, Test2) {
    BigInteger a("10");
    BigInteger b("10");
    BigInteger c("-10");

    ASSERT_TRUE(a == b);
    ASSERT_FALSE(a != b);

    BigInteger e = -22;
    BigInteger f = -22;
    ASSERT_TRUE(e == f);

    BigInteger b1("23142536476869321425364758697");
    BigInteger b2("23142536476869321425364758697");
    ASSERT_TRUE(b1 == b2);
}

TEST(Zero_simple, Test3) {
    BigInteger a("0");
    BigInteger b("-0");

    ASSERT_TRUE(a == b);
    ASSERT_FALSE(a != b);
}

TEST(UnarMinus, Test4) {
    BigInteger a("100");
    BigInteger b("-100");

    ASSERT_TRUE(a == (-b));
    ASSERT_TRUE((-a) == b);
}

TEST(Summation, Test5) {
    SUM_TEST(5, 10)
    SUM_TEST(-5, -10)
    SUM_TEST(5, -10)
    SUM_TEST(-5, 10)

    SUM_TEST(10, 5)
    SUM_TEST(-10, -5)
    SUM_TEST(-10, 5)
    SUM_TEST(10, -5)

    SUM_TEST(0, -0)
    SUM_TEST(0, 0)
    SUM_TEST(0, 1)
    SUM_TEST(0, -1)
}

TEST(LongSum, Test6) {
    BigInteger a("2135467654231523");
    BigInteger b("1234234565134235");
    BigInteger expected("3369702219365758");
    ASSERT_EQ(expected, a + b);
}

TEST(PrefixSum, Test7) {
    BigInteger a(10);
    auto b = ++a;
    ASSERT_EQ(BigInteger(11), a);
    ASSERT_EQ(b, a);

    BigInteger a1("99999999999999999999");
    BigInteger e1("100000000000000000000");
    ++a1;
    ASSERT_EQ(BigInteger("100000000000000000000"), a1);
}

TEST(PostfixSum, Test8) {
    BigInteger a(10);
    auto b = a++;
    ASSERT_EQ(BigInteger(11), a);
    ASSERT_TRUE(b != a);
    ASSERT_EQ(b, a - BigInteger(1));

    BigInteger a1("99999999999999999999");
    BigInteger e1("100000000000000000000");
    a1++;
    ASSERT_EQ(BigInteger("100000000000000000000"), a1);
}

TEST(PrefixSub, Test9) {
    BigInteger a(10);
    auto b = --a;
    ASSERT_EQ(BigInteger(9), a);
    ASSERT_EQ(b, a);

    BigInteger a1("99999999999999999999");
    BigInteger e1("99999999999999999998");
    --a1;
    ASSERT_EQ(e1, a1);
}

TEST(PostfixSub, Test9) {
    BigInteger a(10);
    auto b = a--;
    ASSERT_EQ(BigInteger(9), a);
    ASSERT_TRUE(b != a);
    ASSERT_EQ(b, a + BigInteger(1));

    BigInteger a1("99999999999999999999");
    BigInteger e1("99999999999999999998");
    a1--;
    ASSERT_EQ(e1, a1);
}

TEST(Subtraction, Test10) {
    SUB_TEST(5, 10)
    SUB_TEST(-5, -10)
    SUB_TEST(5, -10)
    SUB_TEST(-5, 10)

    SUB_TEST(10, 5)
    SUB_TEST(-10, -5)
    SUB_TEST(-10, 5)
    SUB_TEST(10, -5)

    SUB_TEST(0, -0)
    SUB_TEST(0, 0)
    SUB_TEST(0, 1)
    SUB_TEST(0, -1)

    SUB_TEST(100000000000000000LL, 1LL)
}

TEST(LongSub, Test11) {
    BigInteger a("2135467654231523");
    BigInteger b("1234234565134235");
    BigInteger expected("901233089097288");
    ASSERT_EQ(expected, a - b);
}

TEST(Multily, Test12) {
    BigInteger a("2135467654231523");
    BigInteger b("1234234565134235");
    BigInteger expected("2635667991578668699758263489905");
    ASSERT_EQ(expected, a * b);
    ASSERT_EQ(-expected, a * (-b));
}

TEST(Division, Test13) {
    BigInteger a("2135467654231523");
    BigInteger b("1234234565134");
    BigInteger e("1730");
    ASSERT_EQ(e, a / b);

    BigInteger a1("2135467654231523345678976543");
    BigInteger b1("12342345651343244535");
    BigInteger e1("173019595");
    ASSERT_EQ(e1, a1 / b1);
    ASSERT_EQ(BigInteger(), b1 / a1);

    ASSERT_THROW(a / BigInteger(0), std::invalid_argument);
}

TEST(Mod, Test14) {
    BigInteger a("2135467654231523345678976543");
    BigInteger b("12342345651343244535");
    BigInteger e("8286103970247313218");
    ASSERT_EQ(e, a % b);
}

TEST(Bool, Test15) {
    BigInteger a(0);
    BigInteger b(2131231);

    ASSERT_TRUE(b);
    ASSERT_FALSE(a);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
