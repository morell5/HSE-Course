#include "biginteger.h"

int BigInteger::getDigit(int i) const {
	return i < this->digits.size() ? this->digits[i] : 0;
}

void BigInteger::trim() {
	while (this->digits.size() > 1 && this->digits.back() == 0) {
		this->digits.pop_back();
	}
}

BigInteger::BigInteger() {
	this->digits.push_back(0);
	sign = 1;
}

BigInteger::BigInteger(int x) {
	*this = BigInteger((long long int) x);
}

BigInteger::BigInteger(long long int x) {
	sign = x >= 0 ? 1 : -1;

	if (x == 0) {
		this->digits.push_back(0);
	}

	while (x) {
		this->digits.push_back(x % BASE);
		x /= BASE;
	}
}

BigInteger::BigInteger(std::string str) {
	this->sign = str.size() && str[0] == '-' ? -1 : 1;

	for (int i = str.size(); i > 0; i -= DIGITS_LEN) {
		std::string substr = i < DIGITS_LEN ? str.substr(0, i) : str.substr(i - DIGITS_LEN, DIGITS_LEN);
		this->digits.push_back(atoi(substr.c_str()));
	}
}

std::string BigInteger::toString() const {
	std::string str = sign == -1 ? "-" : "";

	// Starting from highest digits
	for (int i = digits.size() - 1; i >= 0; i--) {
		str += std::to_string(digits[i]);
	}

	return str;
}

bool BigInteger::operator==(const BigInteger& x) const {
	bool sameSign = x.sign == this->sign;
	bool sameDigits = 1;

	// Comparing all digits
	for (int i = 0; i < x.digits.size() || i < this->digits.size(); i++) {
		if (this->getDigit(i) != x.getDigit(i)) {
			sameDigits = 0;
			break;
		}
	}

	return sameSign && sameDigits;
}

bool BigInteger::operator!=(const BigInteger& x) const {
	return !(*this == x);
}

bool BigInteger::operator>(const BigInteger& x) const {
	int res = false;

	// Comparing signs
	if (this->sign == 1 && x.sign == -1) {
		return true;
	}
	else if (this->sign == -1 && x.sign == 1) {
		return false;
	}

	// Comparing absolute values
	for (int i = std::max(x.digits.size(), this->digits.size()) - 1; i >= 0; i--) {
		if (this->getDigit(i) > x.getDigit(i)) {
			res = true;
			break;
		}
		else if (this->getDigit(i) < x.getDigit(i)) {
			res = false;
			break;
		}
	}

	// If both of numbers are negative
	// |a| > |b| => a < b 
	return this->sign == -1 ? !res : res;
}

bool BigInteger::operator>=(const BigInteger& x) const {
	return *this > x || *this == x;
}

bool BigInteger::operator<(const BigInteger& x) const {
	return !(*this >= x);
}

bool BigInteger::operator<=(const BigInteger& x) const {
	return !(*this > x);
}

BigInteger abs(BigInteger x) {
	x.sign = 1;
	return x;
}

BigInteger max(const BigInteger a, const BigInteger b) {
	return a > b ? a : b;
}

BigInteger min(const BigInteger a, const BigInteger b) {
	return a < b ? a : b;
}

BigInteger BigInteger::operator=(const BigInteger& x) {
	sign = x.sign;
	digits = x.digits;
	return *this;
}

BigInteger BigInteger::operator-() const {
	BigInteger copy = *this;
	copy.sign *= -1;
	return copy;
}

BigInteger BigInteger::operator+(const BigInteger& x) const {
	BigInteger a, b, res;
	int mod = this->sign == x.sign ? 1 : -1, ost = 0;

	// Let be |a| > |b|
	if (abs(*this) > abs(x)) a = *this, b = x;
	else a = x, b = *this;

	res.digits.assign(a.digits.size() + 1, 0);
	res.sign = a.sign;

	for (int i = 0; i < a.digits.size() || i < b.digits.size() || ost != 0; i++) {
		res.digits[i] = a.getDigit(i) + mod * b.getDigit(i) + ost;
		ost = 0;

		if (res.digits[i] >= BASE) {
			res.digits[i] -= BASE;
			ost++;
		}
		else if (res.digits[i] < 0) {
			res.digits[i] += BASE;
			ost--;
		}
	}

	res.trim();
	return res;
}

BigInteger BigInteger::operator-(const BigInteger& x) const {
	return *this + (-x);
}

BigInteger BigInteger::operator*(const BigInteger& x) const {
	BigInteger a = max(*this, x), b = min(*this, x), res; // Let be a > b
	int ost = 0;

	res.sign = a.sign * b.sign;
	res.digits.assign(a.digits.size() + b.digits.size() + 1, 0);

	for (int i = 0; i < b.digits.size(); i++) {
		for (int j = 0; j < a.digits.size() || ost; j++) {
			res.digits[i + j] += a.getDigit(j) * b.getDigit(i) + ost;
			ost = 0;

			if (res.digits[i + j] >= BASE) {
				ost = res.digits[i + j] / BASE;
				res.digits[i + j] %= BASE;
			}
		}
	}

	res.trim();
	return res;
}

BigInteger BigInteger::operator/(const int& x) const {
	if (x == 0) throw "Division by zero";

	BigInteger res;
	std::string dividend = "";

	res.digits.assign(this->digits.size() + 1, 0);

	for (int i = this->digits.size() - 1; i >= 0; i--) {
		dividend += std::to_string(this->digits[i]);
		int temp = stol(dividend);

		if (temp / x > 0) {
			res.digits[i] = temp / x;
			dividend = std::to_string(temp % x);
		}
	}

	res.trim();
	return res;
}

BigInteger BigInteger::operator/(const BigInteger& x) const {
	if (x == BigInteger(0)) throw "Division by zero";

	BigInteger a = abs(*this), b = abs(x);
	BigInteger l = 0, r = a + BigInteger(1);

	while (r - l > BigInteger(1)) {
		BigInteger mid = (l + r) / 2;

		if (b * mid > a) {
			r = mid;
		}
		else {
			l = mid;
		}
	}

	l.sign = this->sign * x.sign;
	return l;
}

BigInteger BigInteger::operator%(const BigInteger& x) const {
	return *this - *this / x * x;
}

BigInteger BigInteger::operator+=(const BigInteger& x) {
	return *this = *this + x;
}

BigInteger BigInteger::operator-=(const BigInteger& x) {
	return *this = *this - x;
}

BigInteger BigInteger::operator*=(const BigInteger& x) {
	return *this = *this * x;
}

BigInteger BigInteger::operator/=(const BigInteger& x) {
	return *this = *this / x;
}

BigInteger BigInteger::operator%=(const BigInteger& x) {
	return *this = *this % x;
}

BigInteger& BigInteger::operator--() {
	*this -= 1;
	return *this;
}

BigInteger BigInteger::operator--(int) {
	BigInteger copy = *this;
	*this -= 1;
	return copy;
}

BigInteger& BigInteger::operator++() {
	*this += 1;
	return *this;
}

BigInteger BigInteger::operator++(int) {
	BigInteger copy = *this;
	*this += 1;
	return copy;
}

BigInteger::operator bool() const {
	return *this != BigInteger(0);
}

std::ostream& operator<<(std::ostream& out, const BigInteger& x) {
	if (x.sign == -1) out << "-";
	out << x.digits.back();

	for (int i = x.digits.size() - 2; i >= 0; i--) {
		std::string digit = std::to_string(x.digits[i]);

		while (digit.size() != x.DIGITS_LEN) {
			digit = "0" + digit;
		}

		out << digit;
	};

	return out;
}

std::istream& operator>>(std::istream& in, BigInteger& x) {
	std::string str;
	in >> str;
	x = BigInteger(str);
	return in;
}