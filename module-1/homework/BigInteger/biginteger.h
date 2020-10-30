
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

	BigInteger& operator=(const BigInteger& copy);

//  BigInteger operator+(const BigInteger &a);
//
//  BigInteger operator-(const BigInteger &a);
//
//  BigInteger operator*(const BigInteger &a);
//
//  BigInteger operator/(const BigInteger &a);
//
//  BigInteger operator%(const BigInteger &a);
//
//  BigInteger &operator+=(const BigInteger &a);
//
//  BigInteger &operator-=(const BigInteger &a);
//
//  BigInteger &operator*=(const BigInteger &a);
//
//  BigInteger &operator/=(const BigInteger &a);
//
//  BigInteger &operator%=(const BigInteger &a);

	BigInteger operator-();

	const BigInteger& operator++();

	const BigInteger operator++(int);

	const BigInteger& operator--();

	const BigInteger operator--(int);

	friend bool operator<(const BigInteger& a, const BigInteger& b);

	friend bool operator==(BigInteger& a, const BigInteger& b);

	friend bool operator!=(BigInteger& a, const BigInteger& b);

	friend bool operator>(BigInteger& a, const BigInteger& b);

	friend bool operator<=(BigInteger& a, const BigInteger& b);

	friend bool operator>=(BigInteger& a, const BigInteger& b);

	friend std::ostream& operator<<(std::ostream& out, const BigInteger& number);

	friend std::istream& operator>>(std::istream& in, BigInteger& number);

	std::string toString() const override;

	operator bool();
 protected:
	bool sign;
};

#endif //BIGINTEGER_BIGINTEGER_H
