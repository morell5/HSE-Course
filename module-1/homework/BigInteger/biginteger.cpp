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
	sign = number >= 0;
}

BigInteger::BigInteger(const BigInteger& copy) : UnsignedBigInteger(copy)
{
	sign = copy.sign;
}

BigInteger::BigInteger(const UnsignedBigInteger& copy) : UnsignedBigInteger(copy)
{
	sign = true;
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
	return !(digits.size() == 1 && digits[0] == '0');

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

bool BigInteger::operator<(const BigInteger& b) const
{
	if (sign < b.sign)
		return true;

	if (b.sign < sign)
		return false;

	if (sign)
	{
		return UnsignedBigInteger::operator<(b);
	}
	else
	{
		return b.operator<(*this);
	}
}

bool BigInteger::operator==(const BigInteger& b) const
{
	return !(*this < b) && !(b < *this);
}

bool BigInteger::operator!=(const BigInteger& b) const
{
	return !(*this == b);
}

bool BigInteger::operator>(const BigInteger& b) const
{
	return (*this >= b) && (*this != b);
}

bool BigInteger::operator<=(const BigInteger& b) const
{
	return (*this < b) || (*this == b);
}

bool BigInteger::operator>=(const BigInteger& b) const
{
	return !(*this < b);
}

BigInteger BigInteger::operator+(const BigInteger& b) const
{
	BigInteger newNumber;

	if (sign == b.sign)
	{
		UnsignedBigInteger buf = *this;
		buf.operator+=(b);
		newNumber = (BigInteger)buf;
		newNumber.sign = sign;
		return newNumber;
	}

	if (UnsignedBigInteger::operator<(b))
	{
		newNumber = (BigInteger)((UnsignedBigInteger)b).operator-(*this);
		newNumber.sign = b.sign;
		return newNumber;
	}

	if (UnsignedBigInteger::operator>(b))
	{
		newNumber = (BigInteger)UnsignedBigInteger::operator-(b);
		newNumber.sign = sign;
		return newNumber;
	}

	return newNumber;
}

BigInteger& BigInteger::operator+=(const BigInteger& b)
{
	if (sign == b.sign)
	{
		UnsignedBigInteger::operator+=(b);
		return *this;
	}

	if (UnsignedBigInteger::operator>=(b))
	{
		UnsignedBigInteger::operator-=(b);

		if (digits.size() == 1 && digits[0] == '0')
			sign = true;

		return *this;
	}
	else
	{
		digits = ((BigInteger)((UnsignedBigInteger)b).operator-(*this)).digits;
		sign = b.sign;
		return *this;
	}
}

BigInteger BigInteger::operator-(const BigInteger& b) const
{
	BigInteger newNum = b;
	newNum.sign ^= true;
	newNum += *this;
	return newNum;
}

BigInteger& BigInteger::operator-=(const BigInteger& b)
{
	sign ^= true;
	operator+=(b);
	sign ^= true;
	return *this;
}

BigInteger BigInteger::operator*(const BigInteger& b) const
{
	BigInteger newNum = (BigInteger)UnsignedBigInteger::operator*(b);
	newNum.sign = !(sign ^ b.sign);
	return newNum;
}

BigInteger& BigInteger::operator*=(const BigInteger& b)
{
	UnsignedBigInteger::operator*=(b);
	sign = !(sign ^ b.sign);
	return *this;
}


