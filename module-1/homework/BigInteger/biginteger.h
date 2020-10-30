
//
// Created by Alex Glushko on 18.09.2020.
//

#ifndef BIGINTEGER_BIGINTEGER_H
#define BIGINTEGER_BIGINTEGER_H

#include "unsigned_biginteger.h"

class BigInteger : protected UnsignedBigInteger
{
 public:
	BigInteger();

	BigInteger(int number);

	BigInteger(const BigInteger& copy);

	BigInteger(const UnsignedBigInteger& copy);

	BigInteger& operator=(const BigInteger& copy);

	BigInteger operator+(const BigInteger& b) const;

	BigInteger operator-(const BigInteger& b) const;

	BigInteger operator*(const BigInteger& b) const;

//	friend BigInteger operator/(const BigInteger& a, const BigInteger& b);
//
//	friend BigInteger operator%(const BigInteger& a, const BigInteger& b);

	BigInteger& operator+=(const BigInteger& b);

	BigInteger& operator-=(const BigInteger& b);

	BigInteger& operator*=(const BigInteger& b);

//  BigInteger &operator/=(const BigInteger &a);
//
//  BigInteger &operator%=(const BigInteger &a);

	BigInteger operator-();

	const BigInteger& operator++();

	const BigInteger operator++(int);

	const BigInteger& operator--();

	const BigInteger operator--(int);

	bool operator<(const BigInteger& b) const;

	bool operator==(const BigInteger& b) const;

	bool operator!=(const BigInteger& b) const;

	bool operator>(const BigInteger& b) const;

	bool operator<=(const BigInteger& b) const;

	bool operator>=(const BigInteger& b) const;

	friend std::ostream& operator<<(std::ostream& out, const BigInteger& number);

	friend std::istream& operator>>(std::istream& in, BigInteger& number);

	std::string toString() const override;

	operator bool();
 protected:
	bool sign;
};

#endif //BIGINTEGER_BIGINTEGER_H
