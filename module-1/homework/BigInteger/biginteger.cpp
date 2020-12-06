#include "biginteger.h"

BigInteger::BigInteger(std::string num) {
	//created
	sign = true;
	if (!num.empty()) {
		if (num[0] == '-') {
			sign = false;
			num = num.substr(1, (long long)num.size() - 1);
		}
		std::reverse(num.begin(), num.end());
	}
	this->num = num;
}
BigInteger::BigInteger(int n) {
	sign = true;
	if (n == 0) {
		this->num = "0";
	}
	else {
		if (n < 0) {
			sign = false;
			num = -n;
		}
		while (n) {
			this->num += (n % 10) + '0';
			n /= 10;
		}
	}
}

BigInteger::BigInteger(const BigInteger& A) {
	this->sign = A.sign;
	this->num = A.num;
}
BigInteger::~BigInteger() {
	//deleted
}
void BigInteger::changeSign() {
	this->sign ^= 1;
}
bool BigInteger::getSign() {
	return this->sign;
}
std::string BigInteger::toString() {
	std::string out;
	out += this->num;
	if (!sign) out += "-";
	std::reverse(out.begin(), out.end());
	return out;
}

void swap(BigInteger& a, BigInteger& b) {
	std::swap(a.num, b.num);
	std::swap(a.sign, b.sign);
}
BigInteger abs(BigInteger a) {
	a.sign = true;
	return a;
}
BigInteger BigInteger::operator+() const {
	return *this;
}
BigInteger BigInteger::operator-() const {
	BigInteger opposite = *this;
	opposite.changeSign();
	return opposite;
}
bool operator<(const BigInteger& a, const BigInteger& b) {
	std::string f = a.num, s = b.num;
	int n = a.num.size() > b.num.size() ? a.num.size() : b.num.size();
	while (f.size() != n) f += '0';
	while (s.size() != n) s += '0';
	std::reverse(f.begin(), f.end());
	std::reverse(s.begin(), s.end());
	if (a.sign) {
		if (b.sign) {
			return f < s;
		}
		else {
			return false;
		}
	}
	else {
		if (b.sign) {
			return true;
		}
		else {
			return f > s;
		}
	}
}
bool operator>(const BigInteger& a, const BigInteger& b) {
	std::string f = a.num, s = b.num;
	int n = a.num.size() > b.num.size() ? a.num.size() : b.num.size();
	while (f.size() != n) f += '0';
	while (s.size() != n) s += '0';
	std::reverse(f.begin(), f.end());
	std::reverse(s.begin(), s.end());
	if (a.sign) {
		if (b.sign) {
			return f > s;
		}
		else {
			return true;
		}
	}
	else {
		if (b.sign) {
			return false;
		}
		else {
			return f < s;
		}
	}
}
bool operator==(const BigInteger& a, const BigInteger& b) {
	return (a.sign == b.sign) && (a.num == b.num);
}
bool operator!=(const BigInteger& a, const BigInteger& b) {
	return !(a == b);
}
bool operator<=(const BigInteger& a, const BigInteger& b) {
	return ((a < b) || (a == b));
}
bool operator>=(const BigInteger& a, const BigInteger& b) {
	return ((a > b) || (a == b));
}
BigInteger operator+(const BigInteger& a, const BigInteger& b) {
	BigInteger res = a;
	res += b;
	return res;
}
BigInteger operator-(const BigInteger& a, const BigInteger& b) {
	BigInteger res = a;
	res -= b;
	return res;
}
BigInteger operator*(const BigInteger& a, const BigInteger& b) {
	BigInteger res;
	res.sign = !(a.sign ^ b.sign);
	res.num = std::string(int(a.num.size()) * int(b.num.size()), '0');
	for (int i = 0; i < a.num.size(); ++i) {
		for (int j = 0; j < b.num.size(); ++j) {
			if (res.num[i + j] > '9') {
				res.num[i + j] -= 10;
				res.num[i + j + 1] += 1;
			}
			int f = a.num[i] - '0';
			int s = b.num[j] - '0';
			res.num[i + j] += (f * s) % 10;
			res.num[i + j + 1] += (f * s) / 10;
			if (res.num[i + j] > '9') {
				res.num[i + j] -= 10;
				res.num[i + j + 1] += 1;
			}
		}
	}
	while (!res.num.empty() && res.num.back() == '0') res.num.pop_back();
	return res;
}
BigInteger get_mid(BigInteger a) {
	BigInteger res;
	std::reverse(a.num.begin(), a.num.end());
	for (int i = 0; i < a.num.size();) {
		if (a.num[i] == '0') {
			res.num += '0';
			i++;
		}
		else if (a.num[i] == '1') {
			if (i != int(a.num.size()) - 1) {
				res.num += ('0' + (10 * (a.num[i] - '0') + (a.num[i + 1] - '0')) / 2);
				if ((10 * (a.num[i] - '0') + (a.num[i + 1] - '0')) % 2) {
					a.num[i + 1] = '1';
					i--;
				}
				i += 2;
			}
			else {
				
				break;
			}
		}
		else {
			res.num += ('0' + (a.num[i] - '0') / 2);
			if ((a.num[i] - '0') % 2) {
				a.num[i] = '1';
				i--;
			}
			i++;
		}
	}
	std::reverse(res.num.begin(), res.num.end());
	return res;
}

BigInteger operator/(const BigInteger& a, const BigInteger& b) {
	bool sgn = !(a.sign ^ b.sign);
	BigInteger l("0"), r = (a.sign?a:-a)+ BigInteger("1");
	while (r - l > BigInteger("1")) {
		BigInteger m = l + get_mid(r - l);
		BigInteger res = m * (b.sign?b:-b);
		if (m * b <= (a.sign ? a : -a)) {
			l = m;
		}
		else {
			r = m;
		}
	}
	l.sign = sgn;
	return l;
}
BigInteger operator%(const BigInteger& a,const BigInteger& b) {
	return a - a / b * b;
}
BigInteger& BigInteger::operator++() {
	*this += BigInteger("1");
	return *this;
}
BigInteger& BigInteger::operator--() {
	*this -= BigInteger("1");
	return *this;
}
BigInteger BigInteger::operator++(int id) {
	BigInteger t = *this;
	*this = *this + BigInteger("1");
	return t;
}
BigInteger BigInteger::operator--(int id) {
	BigInteger t = *this;
	*this = *this - BigInteger("1");
	return t;
}
BigInteger BigInteger::operator+=(const BigInteger& b) {
	if (!this->sign) {
		if (!b.sign) {
			return *this = -((-*this) + (-b));
		}
		else {
			if (abs(b) > abs(*this)) {
				return *this = (b - (-*this));
			}
			else {
				return *this = -((-*this) - b);
			}
		}
	}
	else {
		if (!b.sign) {
			if (abs(*this) > abs(b)) {
				return *this = (*this - (-b));
			}
			else {
				return *this = -((-b) - *this);
			}
		}
		else {
			bool carry = false;
			for (int i = 0;; i++) {
				int sum = (i < this->num.size() ? (this->num[i] - '0') : 0) + (i < b.num.size() ? (b.num[i] - '0') : 0);
				sum += carry;
				carry = false;
				carry |= (sum > 9);
				sum %= 10;
				if (i >= this->num.size()) this->num += '0';
				this->num[i] = sum + '0';
				if (!carry && i + 1 >= (int)this->num.size() && i + 1 >= (int)b.num.size()) break;
			}
			while (this->num.size() > 1 && this->num.back() == '0') this->num.pop_back();
		}
	}
	return *this;
}
BigInteger BigInteger::operator-=(const BigInteger& b) {
	if (!this->sign) {
		if (b.sign) {
			return *this = -((-*this) + b);
		}
		else {
			if (abs(b) > abs(*this)) {
				return *this = ((-b) - (-*this));
			}
			else {
				return *this = -((-*this) - (-b));
			}
		}
	}
	else {
		if (b.sign) {
			if (abs(*this) > abs(b)) {
				bool carry = false;
				for (int i = 0;; i++) {
					int del = (i < this->num.size() ? (this->num[i] - '0') : 0) - (i < b.num.size() ? (b.num[i] - '0') : 0);
					del -= carry;
					carry = false;
					carry |= (del < 0);
					del = (del + 10) % 10;
					if (i >= this->num.size()) this->num += '0';
					this->num[i] = del + '0';
					if (!carry && i + 1 >= (int)this->num.size() && i + 1 >= (int)b.num.size()) break;
				}
				while (this->num.size() > 1 && this->num.back() == '0') this->num.pop_back();
			}
			else {
				return *this = -(b - *this);
			}
		}
		else {
			return *this = (*this + (-b));
		}
	}
	return *this;
}
BigInteger BigInteger::operator*=(const BigInteger& b) {
	*this = *this * b;
	return *this;
}
BigInteger BigInteger::operator/=(const BigInteger& a) {
	*this = *this / a;
	return *this;
}
BigInteger BigInteger::operator%=(const BigInteger& b) {
	*this = *this % b;
	return *this;
}
std::istream& operator>>(std::istream& in, BigInteger& a) {
	std::string s; 
	in >> s;
	a = BigInteger(s);
	return in;
}
std::ostream& operator<<(std::ostream& out, BigInteger a) {
	if (!a.sign) out << '-';
	for (auto it = a.num.rbegin(); it != a.num.rend(); ++it) {
		out << *it;
	}
	return out;
}
BigInteger::operator bool() {
	return !(*this == BigInteger("0"));
}