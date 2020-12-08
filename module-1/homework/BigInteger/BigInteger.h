#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <string>

class BigInteger {
public:

	BigInteger();
	BigInteger(int);
	BigInteger(std::string);

	friend std::istream& operator>>(std::istream&, BigInteger&);
	friend std::ostream& operator<<(std::ostream&, const BigInteger&);

	const BigInteger operator+(const BigInteger&) const;
	const BigInteger operator-(const BigInteger&) const;
	const BigInteger operator*(const BigInteger&) const;
	const BigInteger operator/(const BigInteger&) const;
	const BigInteger operator%(const BigInteger&) const;

	BigInteger& operator+=(const BigInteger&);
	BigInteger& operator-=(const BigInteger&);
	BigInteger& operator*=(const BigInteger&);
	BigInteger& operator/=(const BigInteger&);
	BigInteger& operator%=(const BigInteger&);

	const BigInteger operator-() const;

	BigInteger& operator++();
	BigInteger operator++(int);
	BigInteger& operator--();
	BigInteger operator--(int);

	friend bool operator==(const BigInteger&, const BigInteger&);
	friend bool operator!=(const BigInteger&, const BigInteger&);
	friend bool operator<(const BigInteger&, const BigInteger&);
	friend bool operator>(const BigInteger&, const BigInteger&);
	friend bool operator<=(const BigInteger&, const BigInteger&);
	friend bool operator>=(const BigInteger&, const BigInteger&);

	operator bool() const;
	operator std::string() const;

	std::string toString() const {
		return std::string(*this);
	}

	void deleteZeroes();


private:
	std::vector<int> num;
	bool sign = false;

	static const int BASE = 10000;
	static const int LEN = 4;
};