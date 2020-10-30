//
// Created by Alex on 10.10.2020.
//

#include "unsigned_biginteger.h"

UnsignedBigInteger::UnsignedBigInteger()
{
	digits.push_back('0');
}

UnsignedBigInteger::UnsignedBigInteger(int number)
{
	if (number < 0)
		number = -number;

	std::string sNumber = std::to_string(number);

	for (int i = sNumber.length() - 1; i >= 0; --i)
	{
		digits.push_back(sNumber[i]);
	}

}

UnsignedBigInteger::UnsignedBigInteger(const UnsignedBigInteger& copy)
{
	for (char digit : copy.digits)
	{
		digits.push_back(digit);
	}
}

UnsignedBigInteger::~UnsignedBigInteger()
{
	digits.clear();
}

UnsignedBigInteger& UnsignedBigInteger::operator=(const UnsignedBigInteger& copy)
{
	digits.clear();
	for (char digit : copy.digits)
	{
		digits.push_back(digit);
	}

	return *this;
}

std::ostream& operator<<(std::ostream& out, const UnsignedBigInteger& number)
{
	out << number.toString();
	return out;
}

std::istream& operator>>(std::istream& in, UnsignedBigInteger& number)
{
	char digit = in.get();
	number.digits.clear();

	if (digit < 48 || digit > 57)
	{
		number.digits.push_back('0');
		return in;
	}

	while ((digit = in.get()) >= 48 && digit <= 57)
	{
		number.digits.push_back(digit);
	}

	return in;
}

std::string UnsignedBigInteger::toString() const
{
	std::string buf;
	for (char digit : digits)
	{
		buf = digit + buf;
	}

	return buf;
}

UnsignedBigInteger::operator bool()
{
	if (digits.size() == 1 && digits[0] == '0')
		return false;

	return true;
}

const UnsignedBigInteger& UnsignedBigInteger::operator++()
{
	int i = 0;
	while (digits[i] == '9')
	{
		digits[i] = '0';
		++i;
		if (i >= digits.size())
		{
			digits.push_back('1');
			return *this;
		}
	}
	++digits[i];
	return *this;
}

const UnsignedBigInteger UnsignedBigInteger::operator++(int)
{
	UnsignedBigInteger buf(*this);
	int i = 0;
	while (digits[i] == '9')
	{
		digits[i] = '0';
		++i;
		if (i >= digits.size())
		{
			digits.push_back('1');
			return buf;
		}
	}
	++digits[i];
	return buf;
}

const UnsignedBigInteger& UnsignedBigInteger::operator--()
{
	int i = 0;

	if (digits.size() == 1 && digits[i] == '0')
		return *this;

	while (digits[i] == '0')
	{
		digits[i] = '9';
		++i;
	}

	if (digits[i] == '1' && digits.size() != 1)
		digits.pop_back();
	else
		--digits[i];

	return *this;
}

const UnsignedBigInteger UnsignedBigInteger::operator--(int)
{
	UnsignedBigInteger buf(*this);

	int i = 0;

	if (digits.size() == 1 && digits[i] == '0')
		return buf;

	while (digits[i] == '0')
	{
		digits[i] = '9';
		++i;
	}

	if (digits[i] == '1' && digits.size() != 1)
		digits.pop_back();
	else
		--digits[i];

	return buf;
}

UnsignedBigInteger UnsignedBigInteger::operator+(const UnsignedBigInteger& b) const
{
	UnsignedBigInteger newNumber;
	newNumber.digits.clear();
	char dopNumber = 0;
	size_t i = 0;
	for (; i < std::min(digits.size(), b.digits.size()); ++i)
	{
		char buf = (digits[i] - '0') + (b.digits[i] - '0') + dopNumber;
		newNumber.digits.push_back(buf % 10 + '0');
		dopNumber = buf / 10;
	}

	while (i < digits.size())
	{
		char buf = ((digits[i] - '0') + dopNumber);
		newNumber.digits.push_back(buf % 10 + '0');
		dopNumber = buf / 10;
		++i;
	}

	while (i < b.digits.size())
	{
		char buf = ((b.digits[i] - '0') + dopNumber);
		newNumber.digits.push_back(buf % 10 + '0');
		dopNumber = buf / 10;
		++i;
	}

	if (dopNumber != 0)
		newNumber.digits.push_back(dopNumber + '0');

	return newNumber;
}

UnsignedBigInteger& UnsignedBigInteger::operator+=(const UnsignedBigInteger& b)
{
	char dopNumber = 0;
	size_t i = 0;
	for (; i < std::min(digits.size(), b.digits.size()); ++i)
	{
		char buf = (digits[i] - '0') + (b.digits[i] - '0') + dopNumber;
		digits[i] = buf % 10 + '0';
		dopNumber = buf / 10;
	}

	while (i < digits.size())
	{
		char buf = ((digits[i] - '0') + dopNumber);
		digits[i] = buf % 10 + '0';
		dopNumber = buf / 10;
		++i;
	}

	while (i < b.digits.size())
	{
		char buf = ((b.digits[i] - '0') + dopNumber);
		digits.push_back(buf % 10 + '0');
		dopNumber = buf / 10;
		++i;
	}

	if (dopNumber != 0)
		digits.push_back(dopNumber + '0');

	return *this;
}

bool UnsignedBigInteger::operator<(const UnsignedBigInteger& b) const
{
	if (digits.size() < b.digits.size())
		return true;

	if (digits.size() > b.digits.size())
		return false;

	for (int i = digits.size() - 1; i >= 0; --i)
	{
		if (digits[i] != b.digits[i])
			return digits[i] < b.digits[i];
	}

	return false;
}

bool UnsignedBigInteger::operator>=(const UnsignedBigInteger& b) const
{
	return !(*this < b);
}

bool UnsignedBigInteger::operator==(const UnsignedBigInteger& b) const
{
	return !(*this < b) && !(b < *this);
}

bool UnsignedBigInteger::operator!=(const UnsignedBigInteger& b) const
{
	return !(*this == b);
}

bool UnsignedBigInteger::operator>(const UnsignedBigInteger& b) const
{
	return (*this >= b) && (*this != b);
}

bool UnsignedBigInteger::operator<=(const UnsignedBigInteger& b) const
{
	return (*this < b) || (*this == b);
}

UnsignedBigInteger UnsignedBigInteger::operator-(const UnsignedBigInteger& b) const
{
	UnsignedBigInteger newNumber;

	if (*this <= b)
		return newNumber;
	else
		newNumber.digits.clear();

	size_t i = 0;
	bool nextRank = false;
	for (; i < std::min(digits.size(), b.digits.size()); ++i)
	{
		char buf = b.digits[i] + nextRank;
		if (digits[i] < buf)
		{
			nextRank = true;
			newNumber.digits.push_back((10 - (buf - digits[i])) + '0');
		}
		else
		{
			nextRank = false;
			newNumber.digits.push_back(digits[i] - buf + '0');
		}
	}

	while (i < digits.size() - 1)
	{
		if (nextRank)
		{
			if (digits[i] == '0')
				newNumber.digits.push_back('9');
			else
			{
				newNumber.digits.push_back(digits[i] - nextRank);
				nextRank = false;
			}
		}
		else
		{
			newNumber.digits.push_back(digits[i]);
		}

		++i;
	}

	if (i < digits.size())
	{
		if (nextRank)
		{
			if (digits[i] != '1')
				newNumber.digits.push_back(digits[i] - nextRank);
		}
		else
		{
			newNumber.digits.push_back(digits[i]);
		}
	}

	return newNumber;
}

UnsignedBigInteger& UnsignedBigInteger::operator-=(const UnsignedBigInteger& b)
{
	if (*this <= b)
	{
		digits.clear();
		digits.push_back('0');
		return *this;
	}

	size_t i = 0;
	bool nextRank = false;
	for (; i < std::min(digits.size(), b.digits.size()); ++i)
	{
		char buf = b.digits[i] + nextRank;
		if (digits[i] < buf)
		{
			nextRank = true;
			digits[i] = 10 - (buf - digits[i]) + '0';
		}
		else
		{
			nextRank = false;
			digits[i] = digits[i] - buf + '0';
		}
	}

	while (i < digits.size() - 1)
	{
		if (nextRank)
		{
			if (digits[i] == '0')
				digits[i] = '9';
			else
			{
				digits[i] = digits[i] - nextRank;
				nextRank = false;
			}
		}
		else
		{
			return *this;
		}
		++i;
	}

	if (digits[i] != '1')
		digits[i] = digits[i] - nextRank;
	else
		digits.pop_back();

	return *this;
}

UnsignedBigInteger UnsignedBigInteger::operator*(const UnsignedBigInteger& b) const
{
	//TODO : Fix this shit
	UnsignedBigInteger newNumber;
	if ((b.digits.size() == 1 && b.digits[0] == '0') || (digits.size() == 1 && digits[0] == '0'))
	{
		return newNumber;
	}
	else
	{
		newNumber.digits.clear();
	}

	char dopNum = 0;
	size_t i = 0;

	for (; i < std::min(digits.size(), b.digits.size()); ++i)
	{
		char buf = (digits[i] - '0') * (b.digits[i] - '0');
		newNumber.digits.push_back((buf + dopNum) % 10 + '0');
		dopNum = (buf + dopNum) / 10;
	}

	while (i < digits.size()) {
		char buf = (digits[i] - '0') + dopNum;
		newNumber.digits.push_back(buf % 10 + '0');
		dopNum = buf / 10;
		++i;
	}

	while (i < b.digits.size()) {
		char buf = (b.digits[i] - '0') + dopNum;
		newNumber.digits.push_back(buf % 10 + '0');
		dopNum = buf / 10;
		++i;
	}

	if (dopNum != 0)
		newNumber.digits.push_back(dopNum + '0');

	return newNumber;
}

UnsignedBigInteger& UnsignedBigInteger::operator*=(const UnsignedBigInteger& b)
{
	if ((b.digits.size() == 1 && b.digits[0] == '0') || (digits.size() == 1 && digits[0] == '0'))
	{
		digits.clear();
		digits.push_back('0');
		return *this;
	}

	char dopNum = 0;
	size_t i = 0;

	for (; i < std::min(digits.size(), b.digits.size()); ++i)
	{
		char buf = (digits[i] - '0') * (b.digits[i] - '0');
		digits[i] = (buf + dopNum) % 10 + '0';
		dopNum = (buf + dopNum) / 10;
	}

	while (i < digits.size()) {
		char buf = (digits[i] - '0') + dopNum;
		digits[i] = buf % 10 + '0';
		dopNum = buf / 10;
		++i;
	}

	while (i < b.digits.size()) {
		char buf = (b.digits[i] - '0') + dopNum;
		digits[i] = buf % 10 + '0';
		dopNum = buf / 10;
		++i;
	}

	if (dopNum != 0)
		digits.push_back(dopNum + '0');

	return *this;
}




