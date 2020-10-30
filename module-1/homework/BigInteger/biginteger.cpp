//
// Created by Alex Glushko on 18.09.2020.
//

#include "biginteger.h"

BigInteger::BigInteger()
{
	sign = true;
}

BigInteger::BigInteger(int number) : UnsignedBigInteger(number)
{
	if (number < 0)
	{
		sign = false;
	}
	else
	{
		sign = true;
	}
}

BigInteger::BigInteger(const BigInteger& copy) : UnsignedBigInteger(copy)
{
	sign = copy.sign;
}

BigInteger& BigInteger::operator=(const BigInteger& copy)
{
	digits.clear();
	for (char digit : copy.digits)
	{
		digits.push_back(digit);
	}

	sign = copy.sign;

	return *this;
}

std::string BigInteger::toString() const
{
	std::string buf;
	buf = UnsignedBigInteger::toString();

	if (!sign)
		buf = '-' + buf;

	return buf;
}

std::ostream& operator<<(std::ostream& os, const BigInteger& number)
{
	os << number.toString();
	return os;
}

std::istream& operator>>(std::istream& in, BigInteger& number)
{
	char digit = in.get();
	number.digits.clear();

	if (digit == 45)
	{
		number.sign = false;
		digit = in.get();
		number.digits.push_back(digit);
		if (digit == '0')
		{
			number.sign = true;
			return in;
		}
	}
	else if (digit == 43)
	{
		number.sign = true;
		digit = in.get();
		number.digits.push_back(digit);
		if (digit == '0')
		{
			number.sign = true;
			return in;
		}
	}
	else if (digit >= 49 && digit <= 57)
	{
		number.sign = true;
		number.digits.push_back(digit);
	}
	else
	{
		number.digits.push_back('0');
		number.sign = true;
		return in;
	}

	while ((digit = in.get()) >= 48 && digit <= 57)
	{
		number.digits.push_back(digit);
	}

	return in;
}

BigInteger::operator bool()
{
	if (digits.size() == 1 && digits[0] == '0')
		return false;

	return true;
}

BigInteger BigInteger::operator-()
{
	BigInteger buf(*this);
	buf.sign ^= true;
	return buf;
}

const BigInteger& BigInteger::operator++()
{
	if (sign)
	{
		UnsignedBigInteger::operator++();
		return *this;
	}

	UnsignedBigInteger::operator--();
	if (digits[0] == '0' && digits.size() == 1)
		sign = true;

	return *this;
}

const BigInteger BigInteger::operator++(int)
{
	BigInteger buf(*this);

	if (sign)
	{
		UnsignedBigInteger::operator++();
		return buf;
	}

	UnsignedBigInteger::operator--();
	if (digits[0] == '0' && digits.size() == 1)
		sign = true;

	return buf;
}

const BigInteger& BigInteger::operator--()
{
	if (!sign)
	{
		UnsignedBigInteger::operator++();
		return *this;
	}

	if (digits[0] == '0' && digits.size() == 1)
	{
		digits[0] = '1';
		sign = false;
		return *this;
	}

	UnsignedBigInteger::operator--();
	return *this;
}

const BigInteger BigInteger::operator--(int)
{
	BigInteger buf(*this);

	if (!sign)
	{
		UnsignedBigInteger::operator++();
		return buf;
	}

	if (digits[0] == '0' && digits.size() == 1)
	{
		digits[0] = '1';
		sign = false;
		return buf;
	}

	UnsignedBigInteger::operator--();
	return buf;
}

bool operator<(const BigInteger& a, const BigInteger& b)
{
	if (a.sign < b.sign)
		return true;

	if (b.sign < a.sign)
		return false;

	if (a.sign)
	{
		return a < b;
	}
	else
	{
		return b < a;
	}
}

bool operator==(BigInteger& a, const BigInteger& b)
{
	return !(a < b) && !(b < a);
}

bool operator!=(BigInteger& a, const BigInteger& b)
{
	return !(a == b);
}

bool operator>(BigInteger& a, const BigInteger& b)
{
	return (a >= b) && (a != b);
}

bool operator<=(BigInteger& a, const BigInteger& b)
{
	return (a < b) || (a == b);
}

bool operator>=(BigInteger& a, const BigInteger& b)
{
	return !(a < b);
}


