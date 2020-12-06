#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class BigInteger {
	friend void swap(BigInteger& a, BigInteger& b);
	friend BigInteger abs(BigInteger a);
	friend std::istream& operator>>(std::istream& in, BigInteger& a);
	friend std::ostream& operator<<(std::ostream& out, BigInteger a);
	friend bool operator<(const BigInteger& a, const BigInteger& b);
	friend bool operator>(const BigInteger& a, const BigInteger& b);
	friend bool operator==(const BigInteger& a, const BigInteger& b);
	friend bool operator<= (const BigInteger& a, const BigInteger& b);
	friend bool operator>=(const BigInteger& a, const BigInteger& b);
	friend bool operator!=(const BigInteger& a, const BigInteger& b);
	friend BigInteger operator+(const BigInteger& a, const BigInteger& b);
	friend BigInteger operator-(const BigInteger& a, const BigInteger& b);
	friend BigInteger operator*(const BigInteger& a, const BigInteger& b);
	friend BigInteger operator/(const BigInteger& a, const BigInteger& b);
	friend BigInteger operator%(const BigInteger& a, const BigInteger& b);
	friend BigInteger get_mid(BigInteger a);
private:

	bool sign;
	std::string num;
public:

	BigInteger(std::string num="");
	BigInteger(const BigInteger& A);
	BigInteger(int num);
	~BigInteger();
	void changeSign();
	bool getSign();
	std::string toString();
	BigInteger operator+() const;
	BigInteger operator-() const;
	BigInteger& operator++();
	BigInteger& operator--();
	BigInteger operator++(int id);
	BigInteger operator--(int id);
	BigInteger operator+=(const BigInteger& b);
	BigInteger operator-=(const BigInteger& b);
	BigInteger operator*=(const BigInteger& b);
	BigInteger operator/=(const BigInteger& b);
	BigInteger operator%=(const BigInteger& b);
	operator bool();
};

