#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>
#include <vector>

#include "biginteger.h"
#include "gtest/gtest.h"

TEST(AssignmentFromInt, Test1)
{
	int value = 42;
	BigInteger bigint_val;
	bigint_val = value;

	std::ostringstream oss;
	oss << bigint_val;
	ASSERT_EQ(oss.str(), std::to_string(value));
}

TEST(UnaryMinus, Test1)
{
	int value = 42;
	BigInteger bigint_val = value;
	bigint_val = -bigint_val;

	std::ostringstream oss;
	oss << bigint_val;
	ASSERT_EQ(oss.str(), std::to_string(-value));
}

TEST(ToString, Test1)
{
	int value = 42;
	BigInteger bigint_val = value;

	std::string testString = bigint_val.toString();
	ASSERT_EQ(testString, std::to_string(value));
}

//My test
TEST(Incriment, Test1)
{
	int value = -1;
	BigInteger big_value = value;
	std::string testString = (big_value++).toString();
	ASSERT_EQ(testString, std::to_string(value++));
	testString = (++big_value).toString();
	ASSERT_EQ(testString, std::to_string(++value));
}

TEST(Dicriment, Test1)
{
	int value = 0;
	BigInteger big_value = value;
	std::string testString = (big_value--).toString();
	ASSERT_EQ(testString, std::to_string(value--));
	testString = (--big_value).toString();
	ASSERT_EQ(testString, std::to_string(--value));
}

TEST(Plus, Test1)
{
	int a = -434;
	int b = 43;
	BigInteger big_value_a = a;
	BigInteger big_value_b = b;
	BigInteger answer = big_value_a + big_value_b;
	ASSERT_EQ(answer.toString(), std::to_string(a + b));
}

TEST(PlusEquel, Test1)
{
	int a = -43;
	int b = 4322;
	BigInteger big_value_a = a;
	BigInteger big_value_b = b;
	big_value_a += big_value_b;
	ASSERT_EQ(big_value_a.toString(), std::to_string(a + b));
}

TEST(Minus, Test1)
{
	int a = -4;
	int b = -43;
	BigInteger big_value_a = a;
	BigInteger big_value_b = b;
	BigInteger answer = big_value_a - big_value_b;
	ASSERT_EQ(answer.toString(), std::to_string(a - b));
}

TEST(MinusEq, Test1)
{
	int a = 43;
	int b = -23;
	BigInteger big_value_a = a;
	BigInteger big_value_b = b;
	big_value_a -= big_value_b;
	ASSERT_EQ(big_value_a.toString(), std::to_string(a - b));
}

TEST(Multiply, Test1)
{
	int a = 2332;
	int b = 54;
	BigInteger big_value_a = a;
	BigInteger big_value_b = b;
	big_value_a = big_value_a * big_value_b;
	ASSERT_EQ(big_value_a.toString(), std::to_string(a * b));
}

TEST(MultiplyEq, Test1)
{
	int a = 564;
	int b = 2;
	BigInteger big_value_a = a;
	BigInteger big_value_b = b;
	big_value_a *=  big_value_b;
	ASSERT_EQ(big_value_a.toString(), std::to_string(a * b));
}

//TEST(ToAssignment, Test1) {
//    int val = 42;
//    BigInteger bigint_val = val;
//    bigint_val += bigint_val += bigint_val += bigint_val;
//    val += val += val += val;
//
//    std::ostringstream oss;
//    oss << bigint_val;
//    ASSERT_EQ(oss.str(), std::to_string(val));
//}

//TEST(Arithmetic, Test1) {
//    int a = 42;
//    int b = 11;
//    BigInteger bigint_a = a;
//    BigInteger bigint_b = b;
//
//    ++bigint_a -= bigint_b++;
//    ++a -= b++;
//
//
//    bigint_b -= bigint_a *= bigint_a *= bigint_b;
//    b -= a *= a *= b;
//
//    bigint_a /= 42;
//    a /= 42;
//
//    bigint_a %= 100;
//    a %= 100;
//
//    std::ostringstream oss;
//    oss << bigint_a << bigint_b;
//    ASSERT_EQ(oss.str(), std::to_string(a) + std::to_string(b));
//}
//
//TEST(TypeCast, Test1) {
//    BigInteger bigint_val = 42;
//    ASSERT_TRUE(bool(bigint_val));
//
//    bigint_val = 0;
//    ASSERT_FALSE(bool(bigint_val));
//}
//
//TEST(InStream, Test1) {
//    int value = 42;
//    BigInteger bigint_val = value;
//
//    std::istringstream iss(std::to_string(value));
//    std::ostringstream oss;
//    iss >> bigint_val;
//    oss << bigint_val;
//
//    ASSERT_EQ(oss.str(), std::to_string(value));
//}
//
//TEST(Comparison, Test1) {
//
//   std::istringstream iss("9325492345983274589758023847509283745827349587212938129"
//                              "348762838512387487213648172639471269348172397461297");
//    BigInteger a;
//    BigInteger b;
//    iss >> a >> b;
//
//    std::ostringstream oss;
//    oss << (a <= b) << (a >= b) << (a == b) << (a != b) << (a < b) << (a > b);
//    ASSERT_EQ(oss.str(), "010101");
//}
//
//int main(int argc, char** argv) {
//    ::testing::InitGoogleTest(&argc, argv);
//    return RUN_ALL_TESTS();
//}