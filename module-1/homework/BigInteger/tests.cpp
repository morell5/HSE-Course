#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>
#include <vector>

#include "biginteger.h"
#include "gtest/gtest.h"

TEST(AssignmentFromInt, Test1) {
    int value = 42;
    BigInteger bigint_val;
    bigint_val = value;

    std::ostringstream oss;
    oss << bigint_val;
    ASSERT_EQ(oss.str(), std::to_string(value));
}

TEST(UnaryMinus, Test1) {
    int value = 42;
    BigInteger bigint_val = value;
    bigint_val = -bigint_val;

    std::ostringstream oss;
    oss << bigint_val;
    ASSERT_EQ(oss.str(), std::to_string(-value));
}

TEST(ToString, Test1) {
    int value = 42;
    BigInteger bigint_val = value;

    std::string testString = bigint_val.toString();
    ASSERT_EQ(testString, std::to_string(value));
}

TEST(ToAssignment, Test1) {
    int val = 42;
    BigInteger bigint_val = val;
    bigint_val += bigint_val += bigint_val += bigint_val;
    val += val += val += val;

    std::ostringstream oss;
    oss << bigint_val;
    ASSERT_EQ(oss.str(), std::to_string(val));
}

TEST(Arithmetic, Test1) {
    int a = 42;
    int b = 11;
    BigInteger bigint_a = a;
    BigInteger bigint_b = b;

    ++bigint_a -= bigint_b++;
    ++a -= b++;


    bigint_b -= bigint_a *= bigint_a *= bigint_b;
    b -= a *= a *= b;

    bigint_a /= 42;
    a /= 42;

    bigint_a %= 100;
    a %= 100;

    std::ostringstream oss;
    oss << bigint_a << bigint_b;
    ASSERT_EQ(oss.str(), std::to_string(a) + std::to_string(b));
}

TEST(TypeCast, Test1) {
    BigInteger bigint_val = 42;
    ASSERT_TRUE(bool(bigint_val));

    bigint_val = 0;
    ASSERT_FALSE(bool(bigint_val));
}

TEST(InStream, Test1) {
    int value = 42;
    BigInteger bigint_val = value;

    std::istringstream iss(std::to_string(value));
    std::ostringstream oss;
    iss >> bigint_val;
    oss << bigint_val;

    ASSERT_EQ(oss.str(), std::to_string(value));
}

TEST(Comparison, Test1) {
    std::istringstream iss("9325492345983274589758023847509283745827349587212938129 "
                           "348762838512387487213648172639471269348172397461297");
    BigInteger a;
    BigInteger b;
    iss >> a >> b;

    std::ostringstream oss;
    oss << (a <= b) << (a >= b) << (a == b) << (a != b) << (a < b) << (a > b);
    ASSERT_EQ(oss.str(), "010101");
}

TEST(HighLoad, Test1) {
    BigInteger n = 1;
    for (int i = 1; i <= 300; ++i)
        n *= i;

    std::ostringstream oss;
    oss << n;
    ASSERT_EQ(oss.str(), "3060575122164406360353704612972686293885888041735769994167"
                         "7674125947653317671686746551529142247757334993914788870172"
                         "6368864263907759003154226842927906974559841225476930271954"
                         "6040080122157762521768542559653569035067887252643218962642"
                         "9936520457644883038890975394348962543605322598077652127082"
                         "2437639449120128678675368305712293681943649956460498166450"
                         "2277165001851765464693401122260347297240663332585835068701"
                         "5016979416885035375213755491028912640715715483028228493795"
                         "2636580145235233156936482233436799254594095276820608062232"
                         "8123873838808170496000000000000000000000000000000000000000"
                         "00000000000000000000000000000000000");
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
