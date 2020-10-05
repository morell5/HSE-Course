#include "biginteger.h"

const int32_t& max(const int32_t& a, const int32_t& b) {
	return (a < b ? b : a);
}

const int32_t& min(const int32_t& a, const int32_t& b) {
	return (a < b ? a : b);
}

void reverse(std::string& str) {
	for (std::size_t i = 0; i < str.size() / 2; i++) {
		char c = str[i];
		str[i] = str[str.size() - i - 1];
		str[str.size() - i - 1] = c;
	}
}

void BigInteger::set_left_null(BigInteger& bigInt) {
	for (std::size_t i = 0; i < bigInt.block_count; i++)
		if (bigInt.number[i] > 0)
			bigInt.leftNull = static_cast<uint32_t>(i + 1);
}

const BigInteger BigInteger::abs_with_copy(const BigInteger& bigInt) {
	BigInteger result = bigInt;
	result.is_neg = false;
	return result;
}

const BigInteger& BigInteger::sum_abs(BigInteger& a, const BigInteger& b) {
	uint32_t currSum = 0;
	for (std::size_t i = 0; i < a.block_count; i++) {
		a.number[i] = (currSum + a.number[i] + b.number[i]) % a.block_max; 
		currSum = (currSum + a.number[i] + b.number[i]) / a.block_max;
	}

	BigInteger::set_left_null(a);
	return a;
}

std::size_t BigInteger::find_next_pos(const BigInteger& a, const std::size_t pos) {
	std::size_t next = -1;
	for (std::size_t i = pos + 1; i < a.block_count; i++)
		if (a.number[i] > 0) {
			next = i;
			break;
		}
	return next;
}

void BigInteger::make_sub(const std::size_t l, const std::size_t r, BigInteger& a, const BigInteger& b, bool rev) {
	for (std::size_t i = l; i < r; i++)
		if (rev == false)
			a.number[i] = static_cast<uint32_t>(1e9 - 1) - b.number[i];
		else
			a.number[i] = static_cast<uint32_t>(1e9 - 1) - a.number[i]; 
}

const BigInteger& BigInteger::substraction_from_left(BigInteger& a, const BigInteger& b) {
	for (std::size_t i = 0; i < a.block_count; i++) {
		if (a.number[i] >= b.number[i]) {
			a.number[i] -= b.number[i];
			continue;
		}

		std::size_t next = BigInteger::find_next_pos(a, i);
		BigInteger::make_sub(i + 1, next, a, b, false);

		a.number[i] = static_cast<uint32_t>(1e9) - b.number[i] + a.number[i];
		a.number[next]--;
		i = next - 1;
	}

	BigInteger::set_left_null(a);
	return a;
}

const BigInteger& BigInteger::substraction_from_right(BigInteger& a, const BigInteger& b) {
	for (std::size_t i = 0; i < a.block_count; i++) {
		if (b.number[i] >= a.number[i]) {
			a.number[i] = b.number[i] - a.number[i];
			continue;
		}

		std::size_t next = BigInteger::find_next_pos(b, i);
		BigInteger::make_sub(i + 1, next, a, b, true);

		a.number[i] = static_cast<uint32_t>(1e9) - a.number[i] + b.number[i];
		a.number[next]++;
		i = next - 1;
	}

	return a;
}

const std::vector<BigInteger> BigInteger::split(const BigInteger& bigInt, const std::size_t& size) {
	BigInteger first, second;

	for (std::size_t i = 0; i < size / 2; i++)
		second.number[i] = bigInt.number[i];
	
	for (std::size_t i = size / 2; i < bigInt.leftNull; i++)
		first.number[i - size / 2] = bigInt.number[i];

	BigInteger::set_left_null(first);
	BigInteger::set_left_null(second);

	std::vector <BigInteger> result = {first, second};
	return result;
}

const BigInteger BigInteger::mult10(const BigInteger& bigInt, const std::size_t& exponent) {
	BigInteger result;
	for (std::size_t i = exponent; i < bigInt.block_count; i++)
		result.number[i] = bigInt.number[i - exponent]; 

	BigInteger::set_left_null(result);
	return result;
} 

const BigInteger BigInteger::mult(const std::size_t size, BigInteger x, BigInteger y) {
	if (x == 0 or x == 0)
		return 0;
	
	if (size == 1) {
		BigInteger result;

		result.number[0] = static_cast<uint32_t>((static_cast<uint64_t>(x.number[0]) * static_cast<uint64_t>(y.number[0])) % result.block_max);
		result.number[1] = static_cast<uint32_t>((static_cast<uint64_t>(x.number[0]) * static_cast<uint64_t>(y.number[0])) / result.block_max);

		BigInteger::set_left_null(result);
		return result;
	}

	std::vector <BigInteger> splitted_x = BigInteger::split(x, size);
	std::vector <BigInteger> splitted_y = BigInteger::split(y, size);

	BigInteger a = splitted_x[0];
	BigInteger b = splitted_x[1];
	BigInteger c = splitted_y[0];
	BigInteger d = splitted_y[1];

	BigInteger first_factor = mult(max(a.leftNull, c.leftNull), a, c);
	BigInteger third_factor = mult(max(b.leftNull, d.leftNull), b, d);
	BigInteger second_factor = mult(max((a + b).leftNull, (c + d).leftNull), a + b, c + d) - first_factor - third_factor;
	
	BigInteger shifted_first_factor = BigInteger::mult10(first_factor, 2 * (size / 2));
	BigInteger shifted_second_factor = BigInteger::mult10(second_factor, size / 2);
	BigInteger result = shifted_first_factor + shifted_second_factor + third_factor;

	BigInteger::set_left_null(result);
	return result;
}

const BigInteger BigInteger::div2(const BigInteger& bigInt) {
	BigInteger result;

	int32_t remainder = 0;
	for (std::size_t i = bigInt.leftNull - 1; i + 1 != 0; i--) {
		result.number[i] = (remainder * static_cast<uint32_t>(1e9) + bigInt.number[i]) / 2;
		remainder = (remainder * static_cast<uint32_t>(1e9) + bigInt.number[i]) % 2;
	}

	BigInteger::set_left_null(result);
	return result;
}

const BigInteger BigInteger::div_abs(const BigInteger& a, const BigInteger& b) {
	BigInteger l = 0, r = BigInteger::abs_with_copy(a) + 1;

	while (r - l > 1) {
		BigInteger m = div2(l + r);
		if (BigInteger::abs_with_copy(a) >= m * BigInteger::abs_with_copy(b))
			l = m;
		else
			r = m;
	}

	BigInteger::set_left_null(l);
	return l;
}

bool BigInteger::less(const BigInteger& a, const BigInteger& b) {
	for (std::size_t i = 0; i < std::max(a.leftNull, b.leftNull); i++)
		if (a.number[i] != b.number[i])
			return a.number[i] < b.number[i];
	return false;
}

BigInteger::BigInteger(): 
	block_max(static_cast<uint32_t>(1e9)), 
	block_count(128), 
	leftNull(0), 
	number(128, 0), 
	is_neg(false) 
{};

BigInteger::BigInteger(const BigInteger& bigInt): 
	block_max(bigInt.block_max), 
	block_count(bigInt.block_count), 
	leftNull(bigInt.leftNull), 
	number(bigInt.number), 
	is_neg(bigInt.is_neg) 
{};

BigInteger::operator bool() {
	return (this->leftNull != 0);
}

BigInteger::BigInteger(int64_t _number): block_max(static_cast<uint32_t>(1e9)), block_count(128) {
	number.assign(128, 0);
	number[1] = static_cast<uint32_t>(std::abs(_number)) / block_max;
	number[0] = static_cast<uint32_t>(std::abs(_number)) % block_max;

	is_neg = (_number < 0);
	BigInteger::set_left_null(*this);
};

void BigInteger::swap(BigInteger& a, BigInteger& b) {
	std::swap(a.number, b.number);
	std::swap(a.is_neg, b.is_neg);
	std::swap(a.leftNull, b.leftNull);
}

const BigInteger BigInteger::StringToBigInteger(std::string& strNumber) {
	BigInteger result;

	if (strNumber[0] == '-') {
		result.is_neg = 1;
		strNumber.erase(0, 1);
	}

	reverse(strNumber);
	uint32_t currNumber = 0;
	for (std::size_t i = 0; i < strNumber.size(); i += 9) {
		std::string currStr = strNumber.substr(i, min(9, static_cast<int32_t>(strNumber.size()) - static_cast<int32_t>(i)));

		reverse(currStr);
		currNumber += std::stoi(currStr);

		result.number[i / 9] = currNumber % result.block_max;
		currNumber /= result.block_max;
	}

	BigInteger::set_left_null(result);
	return result;
}

std::string BigInteger::BigIntegerToString(const BigInteger& bigInt) {
	if (bigInt.leftNull == 0)
		return "0";

	std::string result = (bigInt.is_neg ? "-" : "");
	for (int32_t i = static_cast<int32_t>(bigInt.leftNull) - 1; i >= 0; i--) {
		std::string add = std::to_string(bigInt.number[i]);
		
		while (add.size() < 9 and i < static_cast<int32_t>(bigInt.leftNull) - 1)
			add = "0" + add;
		
		result += add;
	}

	return result;
}

std::string BigInteger::toString() {
	return BigInteger::BigIntegerToString(*this);
}

BigInteger& BigInteger::operator=(const BigInteger& bigInt) {
	this->number = bigInt.number;
	this->is_neg = bigInt.is_neg;
	this->leftNull = bigInt.leftNull;
	return *this;
}

BigInteger& BigInteger::operator+=(const BigInteger& bigInt) {
	if (this->is_neg == bigInt.is_neg)
		*this = BigInteger::sum_abs(*this, bigInt);
	else if (bigInt.is_neg)
		*this = ((this->is_neg = BigInteger::less(*this, bigInt)) ? BigInteger::substraction_from_right(*this, bigInt) : BigInteger::substraction_from_left(*this, bigInt));
	return *this;
}

BigInteger& BigInteger::operator-=(const BigInteger& bigInt) {
	return *this += (-bigInt);	
}

BigInteger& BigInteger::operator*=(const BigInteger& bigInt) {
	*this = BigInteger::mult(std::max(this->leftNull, bigInt.leftNull), *this, bigInt);
	this->is_neg ^= bigInt.is_neg;
	return *this;
}

BigInteger& BigInteger::operator/=(const BigInteger& bigInt) {
	*this = BigInteger::div_abs(*this, bigInt);
	this->is_neg ^= bigInt.is_neg;
	return *this;
}

BigInteger& BigInteger::operator%=(const BigInteger& bigInt) {
	*this = *this - bigInt * (*this / bigInt);
	return *this;
}

std::istream& operator>>(std::istream& in, BigInteger& bigInt) {
	std::string strNumber;	
	in >> strNumber;
	bigInt = BigInteger::StringToBigInteger(strNumber);
	return in;
}

std::ostream& operator<<(std::ostream& out, const BigInteger& bigInt) {
	out << BigInteger::BigIntegerToString(bigInt);
	return out;
}

const BigInteger operator+(const BigInteger& a, const BigInteger& b) {
	BigInteger result = a;
	result += b;
	return result;
}

const BigInteger operator-(const BigInteger& a, const BigInteger& b) {
	BigInteger result = a;
	result -= b;
	return result;
}

const BigInteger operator-(const BigInteger& bigInt) {
	BigInteger result = bigInt;
	result.is_neg ^= 1;
	return result;
}

const BigInteger operator*(const BigInteger& a, const BigInteger& b) {
	BigInteger result = a;
	result *= b;
	return result;
}

const BigInteger operator/(const BigInteger& a, const BigInteger& b) {
	BigInteger result = a;
	result /= b;
	return result;
}

const BigInteger operator%(const BigInteger& a, const BigInteger& b) {
	BigInteger result = a;
	result %= b;
	return result;
}

BigInteger& operator++(BigInteger& bigInt) {
	bigInt += 1;
	return bigInt;
}

BigInteger operator++(BigInteger& bigInt, int) {
	BigInteger oldBigInt = bigInt;
	++bigInt;
	return oldBigInt;
}

BigInteger& operator--(BigInteger& bigInt) {
	bigInt -= 1;
	return bigInt;
}

BigInteger operator--(BigInteger& bigInt, int) {
	BigInteger oldBigInt = bigInt;
	--bigInt;
	return oldBigInt;
}

bool operator<(const BigInteger& a, const BigInteger& b) {
	if (a.is_neg == b.is_neg)
		return a.is_neg ^ BigInteger::less(a, b);
	return a.is_neg;
}	

bool operator>(const BigInteger& a, const BigInteger& b) {
	return (b < a);
}

bool operator==(const BigInteger& a, const BigInteger& b) {
	return !(a < b) and !(b < a);
}

bool operator!=(const BigInteger& a, const BigInteger& b) {
	return !(a == b);
}

bool operator<=(const BigInteger& a, const BigInteger& b) {
	return !(a > b);
}

bool operator>=(const BigInteger& a, const BigInteger& b) {
	return !(a < b);
}