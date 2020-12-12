#include "BigInteger.h"

BigInteger::BigInteger() {

}

BigInteger::BigInteger(int a) {
	sign = a < 0;
	a = abs(a);
	do {
		num.push_back(a % BASE);
		a /= BASE;
	} while (a > 0);
}

BigInteger::BigInteger(std::string str) {
	if (str.size() > 0) {
		if (str[0] == '-') {
			sign = true;
			str = str.substr(1);
		}
		for (int i = str.size(); i > 0; i -= LEN) {
			num.push_back(std::stoi(str.substr((i > LEN ? i - LEN : 0), LEN)));
		}
	}
}

std::istream& operator>>(std::istream& in, BigInteger& a) {
	std::string str;
	in >> str;
	a = BigInteger(str);
	return in;
}

std::ostream& operator<<(std::ostream& out, const BigInteger& a) {
	if (a.num.empty()) {
		out << 0;
	}
	else {
		if (a.sign) {
			out << '-';
		}
		out << a.num.back();
		for (int i = a.num.size() - 2; i >= 0; i--) {
			out << std::setfill('0') << std::setw(a.LEN) << a.num[i];
		}
	}
	return out;
}

const BigInteger BigInteger::operator-() const {
	BigInteger res(*this);
	res.sign = !res.sign;
	return res;
}

BigInteger& BigInteger::operator++() {
	return *this += 1;
}

BigInteger BigInteger::operator++(int) {
	BigInteger res = *this;
	*this += 1;
	return res;
}

BigInteger& BigInteger::operator--() {
	return *this -= 1;
}

BigInteger BigInteger::operator--(int) {
	BigInteger res = *this;
	*this -= 1;
	return res;
}

bool operator==(const BigInteger& a, const BigInteger& b) {
	if (a.sign != b.sign) {
		return false;
	}
	if (a.num.empty()) {
		return b.num.empty() || b.num.size() == 1 && b.num[0] == 0;
	}
	if (b.num.empty()) {
		return a.num.size() == 1 && a.num[0] == 0;
	}
	if (a.num.size() != b.num.size()) {
		return false;
	}
	for (std::size_t i = 0; i < a.num.size(); i++) {
		if (a.num[i] != b.num[i]) {
			return false;
		}
	}
	return true;
}

bool operator!=(const BigInteger& a, const BigInteger& b) {
	return !(a == b);
}

bool operator<(const BigInteger& a, const BigInteger& b) {
	if (a.sign) {
		if (!b.sign) {
			return true;
		}
		return ((-b) < (-a));
	}
	if (b.sign) {
		return false;
	}
	if (a.num.size() != b.num.size()) {
		return a.num.size() < b.num.size();
	}
	for (std::size_t i = a.num.size() - 1; i >= 0; i--) {
		if (a.num[i] != b.num[i]) {
			return a.num[i] < b.num[i];
		}
	}
	return false;
}

bool operator>(const BigInteger& a, const BigInteger& b) {
	return b < a;
}

bool operator<=(const BigInteger& a, const BigInteger& b) {
	return !(a > b);
}

bool operator>=(const BigInteger& a, const BigInteger& b) {
	return !(a < b);
}


BigInteger& BigInteger::operator+=(const BigInteger& other) {
	if (sign) {
		if (other.sign) {
			return *this = -(-(*this) + (-other));
		}
		else {
			return *this = other - (-(*this));
		}
	}
	else if (other.sign) {
		return *this = *this - (-other);
	}

	int carry = 0;
	for (std::size_t i = 0; i < std::max(num.size(), other.num.size()) || carry > 0; i++) {
		if (i == num.size()) {
			num.push_back(0);
		}
		num[i] += carry + (i < other.num.size() ? other.num[i] : 0);
		carry -= BASE;
	}

	return *this;
}

const BigInteger BigInteger::operator+(const BigInteger& other) const {
	BigInteger res = *this;
	res += other;
	return res;
}

BigInteger& BigInteger::operator-=(const BigInteger& other) {
	if (other.sign) {
		return *this = *this + (-other);
	}
	else if (sign) {
		return *this = -(-(*this) + other);
	}
	else if (*this < other) {
		return *this = -(other - *this);
	}

	int carry = 0;
	for (std::size_t i = 0; i < other.num.size() || carry > 0; i++) {
		num[i] -= carry + (i < other.num.size() ? other.num[i] : 0);
		carry = num[i] < 0;
		if (carry) {
			num[i] += BASE;
		}
	}

	deleteZeroes();
	return *this;
}

const BigInteger BigInteger::operator-(const BigInteger& other) const {
	BigInteger res = *this;
	res -= other;
	return res;
}


BigInteger& BigInteger::operator*=(const BigInteger& other) {
	return *this = *this * other;
}

const BigInteger BigInteger::operator*(const BigInteger& other) const {
	BigInteger res;
	res.num.resize(num.size() + other.num.size());
	for (std::size_t i = 0; i < num.size(); i++) {
		int carry = 0;
		for (std::size_t j = 0; j < other.num.size() || carry > 0; j++) {
			int cur = res.num[i + j] + num[i] * (j < other.num.size() ? other.num[j] : 0) + carry;
			res.num[i + j] = cur % BASE;
			carry = cur / BASE;
		}
	}

	res.sign = sign != other.sign;
	res.deleteZeroes();
	return res;
}

BigInteger& BigInteger::operator/=(const BigInteger& other) {
	return *this = *this / other;
}

const BigInteger BigInteger::operator/(const BigInteger& other) const {
	BigInteger res;
	BigInteger a = *this;
	while (a > other) {
		a -= other;
		++res;
	}
	return res;
}

BigInteger& BigInteger::operator%=(const BigInteger& other) {
	*this -= (*this / other) * other;
	if (sign) {
		*this += other;
	}
	return *this;
}

const BigInteger BigInteger::operator%(const BigInteger& other) const {
	BigInteger res = *this;
	res %= other;
	return res;
}

BigInteger::operator bool() const {
	return num[0] != 0;
}

BigInteger::operator std::string() const {
	std::stringstream ss;
	ss << *this;
	return ss.str();
}

void BigInteger::deleteZeroes() {
	while (num.size() > 1 && num.back() == 0) {
		num.pop_back();
	}
}