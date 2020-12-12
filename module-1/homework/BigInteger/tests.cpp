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

TEST(AssigmentFromOther, Test1) {
    int value = 42;
    BigInteger bigint_val;
    bigint_val = value;
    BigInteger other = bigint_val;

    ASSERT_TRUE(other == bigint_val);
    ASSERT_FALSE(other != bigint_val);

    other += 1;
    ASSERT_FALSE(other == bigint_val);
    ASSERT_TRUE(other != bigint_val);

    BigInteger other2 = bigint_val + other;
    ASSERT_FALSE(other2 == bigint_val);
    ASSERT_FALSE(other2 == other);
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

TEST(Multiply, Test1) {
    long long v = 1034567891;
    BigInteger bigint_val = v;
    bigint_val *= bigint_val;
    v *= v;

    std::ostringstream oss;
    oss << bigint_val;
    ASSERT_EQ(oss.str(), std::to_string(v));
}

TEST(Multiply, Test2) {
    long long v = 1034567891;
    BigInteger bigint_val = v;
    bigint_val *= bigint_val;
    v *= v;

    std::string s = "";
    bigint_val *= BigInteger::ten_pow(30);
    for (int i = 0; i < 30; ++i)
        s += '0';

    std::ostringstream oss;
    oss << bigint_val;
    ASSERT_EQ(oss.str(), std::to_string(v) + s);
}

TEST(Divide, Test1) {
    long long v = 1034567891;
    BigInteger bigint_val = v;
    bigint_val /= bigint_val;
    v /= v;

    std::string s = "";
    bigint_val *= BigInteger::ten_pow(30);
    for (int i = 0; i < 30; ++i)
        s += '0';

    std::ostringstream oss;
    oss << bigint_val;
    ASSERT_EQ(oss.str(), std::to_string(v) + s);
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


TEST(Arithmetic, Test2) {

    BigInteger bigint_a = 1;

    for (int i = 1; i < 101; ++i)
        bigint_a *= i;

    std::ostringstream oss;
    oss << bigint_a;
    ASSERT_EQ(oss.str(), "9332621544394415268169923885626670049"
                         "0715968264381621468592963895217599993"
                         "2299156089414639761565182862536979208"
                         "2722375825118521091686400000000000000"
                         "0000000000");
}


TEST(Arithmetic, Test3) {

    BigInteger bigint_a = -5;
    BigInteger bigint_b = 5;

    for (int i = 1; i < 101; ++i){
        bigint_a += 1;
        bigint_b--;
    }

    std::ostringstream oss;
    oss << bigint_a << " " << bigint_b;
    ASSERT_EQ(oss.str(), "95 -95");
}

TEST(TypeCast, Test1) {
    BigInteger bigint_val = 42;
    ASSERT_TRUE(bool(bigint_val));
    
    bigint_val = 0;
    ASSERT_FALSE(bool(bigint_val));
}


TEST(Half, Test1) {
    BigInteger bigint_val = 1000000000;
    bigint_val *= bigint_val;
    bigint_val += 5;

    bigint_val = bigint_val.half();

    std::ostringstream oss;
    oss << bigint_val;
    ASSERT_EQ(oss.str(), "500000000000000002");
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

   std::istringstream iss("9325492345983274589758023847509283745827349587212938129"
                              "348762838512387487213648172639471269348172397461297");
    BigInteger a;
    BigInteger b;
    iss >> a >> b;

    std::ostringstream oss;
    oss << (a <= b) << (a >= b) << (a == b) << (a != b) << (a < b) << (a > b);
    ASSERT_EQ(oss.str(), "010101");
}

TEST(Comparison, Test2) {

    std::istringstream iss("9325492345983274589758023847509283745827349587212938129"
                           "-348762838512387487213648172639471269348172397461297");
    BigInteger a;
    BigInteger b;
    iss >> a >> b;

    ASSERT_EQ(a.toString(), "9325492345983274589758023847509283745827349587212938129");
    ASSERT_EQ(b.toString(), "-348762838512387487213648172639471269348172397461297");

    std::ostringstream oss;
    oss << (a <= b) << (a >= b) << (a == b) << (a != b) << (a < b) << (a > b);
    ASSERT_EQ(oss.str(), "010101");
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}