//
// Created by Alex on 10.10.2020.
//

#ifndef BIGINTEGER__UNSIGNED_BIGINTEGER_H_
#define BIGINTEGER__UNSIGNED_BIGINTEGER_H_

#include <climits>
#include <iostream>
#include <string>
#include <vector>

class UnsignedBigInteger
{
 public:
	UnsignedBigInteger();

	UnsignedBigInteger(int number);

	UnsignedBigInteger(const UnsignedBigInteger& copy);

	~UnsignedBigInteger();

	friend bool operator<(const UnsignedBigInteger& a, const UnsignedBigInteger& b);

	friend bool operator==(const UnsignedBigInteger& a, const UnsignedBigInteger& b);

	friend bool operator!=(const UnsignedBigInteger& a, const UnsignedBigInteger& b);

	friend bool operator>(const UnsignedBigInteger& a, const UnsignedBigInteger& b);

	friend bool operator<=(const UnsignedBigInteger& a, const UnsignedBigInteger& b);

	friend bool operator>=(const UnsignedBigInteger& a, const UnsignedBigInteger& b);

	UnsignedBigInteger& operator=(const UnsignedBigInteger& copy);

	friend UnsignedBigInteger operator+(const UnsignedBigInteger& a, const UnsignedBigInteger& b);

	friend UnsignedBigInteger operator-(const UnsignedBigInteger& a, const UnsignedBigInteger& b);

//	friend UnsignedBigInteger operator*(const UnsignedBigInteger& a, const UnsignedBigInteger& b);

//  friend UnsignedBigInteger operator/(const UnsignedBigInteger &a, const UnsignedBigInteger& b);
//
//  friend UnsignedBigInteger operator%(const UnsignedBigInteger &a, const UnsignedBigInteger& b);

	UnsignedBigInteger& operator+=(const UnsignedBigInteger& a);

	UnsignedBigInteger& operator-=(const UnsignedBigInteger& a);

//	UnsignedBigInteger& operator*=(const UnsignedBigInteger& a);

//  UnsignedBigInteger &operator/=(const UnsignedBigInteger &a);
//
//  UnsignedBigInteger &operator%=(const UnsignedBigInteger &a);

	const UnsignedBigInteger& operator++();

	const UnsignedBigInteger operator++(int);

	const UnsignedBigInteger& operator--();

	const UnsignedBigInteger operator--(int);

	friend std::ostream& operator<<(std::ostream& out, const UnsignedBigInteger& number);

	friend std::istream& operator>>(std::istream& in, UnsignedBigInteger& number);

	virtual std::string toString() const;

	operator bool();

 protected:
	std::vector<char> digits;
};

#endif //BIGINTEGER__UNSIGNED_BIGINTEGER_H_
