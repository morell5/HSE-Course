#include "biginteger.h"

void BigInteger::convertNum(std::vector<int> &number, std::string& strNum) {
    for (long long i = strNum.size(); i > 0; i -= 9) {
        if (i >= 9) {
            number.push_back(atoi(strNum.substr(i - 9, 9).c_str()));
        } else {
            number.push_back(atoi(strNum.substr(0, i).c_str()));
        }
    }
}


BigInteger::BigInteger(int integer) {
    isNegative = integer < 0;

    std::string tmp = std::to_string(integer);
    number.clear();
    convertNum(number, tmp);
}

BigInteger::BigInteger(std::string num) {
    if (num.size() == 0) {
        isNegative = 0;
        number = std::vector<int>(1, 0);
    } else {
        isNegative = (num[0] == '-');
        convertNum(number, num);
    }

}

BigInteger &BigInteger::operator=(int integer) {
    isNegative = integer < 0;

    std::string tmp = std::to_string(integer);
    number.clear();
    for (int i=(int)tmp.length(); i > 0; i -= 9) {
        if (i < 9) {
            number.push_back(atoi(tmp.substr(0, i).c_str()));
        } else {
            number.push_back(atoi(tmp.substr(i - 9, 9).c_str()));
        }
    }
    return *this;
}

BigInteger& BigInteger::operator=(const BigInteger& num) {
    isNegative = num.isNegative;
    number = num.number;
    return *this;
}

std::istream& operator>>(std::istream &in, BigInteger &num) {
    std::string number;
    in >> number;
    num = BigInteger(number);
    return in;
}

std::ostream& operator<<(std::ostream &out, const BigInteger &num) {
    out << num.toString();
    return out;
}

std::string BigInteger::toString() const {
    std::string res;
    if (isNegative) {
        res += "-";
    }
    res += number.empty() ? 0 : std::to_string(number.back());
    for (int i = (int)number.size() - 2; i >= 0; --i) {
        res += std::to_string(number[i]);
    }
    return res;
}

const BigInteger& operator+(const BigInteger& num) {
    return num;
}

const BigInteger BigInteger::operator-() const {
    BigInteger res(!isNegative, number);
    return res;
}

bool operator==(const BigInteger& left, const BigInteger& right) {
    return (left.isNegative == right.isNegative && left.number == right.number);
}

bool operator>(const BigInteger& left, const BigInteger& right) {
    if (left == right) {
        return false;
    }

    if (left.isNegative && !right.isNegative) {
        return false;
    }

    if (!left.isNegative && right.isNegative) {
        return true;
    }

    bool allNegative = left.isNegative && right.isNegative;

    if (left.number.size() < right.number.size()) {
        return !allNegative;
    }

    for (int i = left.number.size() - 1; i >= 0; --i) {
        if (left.number[i] < right.number[i] && allNegative) {
            return true;
        }

        if (left.number[i] > right.number[i] && !allNegative) {
            return true;
        }
    }

    return false;
}

BigInteger operator+(const BigInteger& left, const BigInteger& right) {
    if (left.isNegative) {
        if (right.isNegative) {
            return -((-left) + (-right));
        }
        return right - (-left);
    }
    if (right.isNegative)
    {
        return right + left;
    }

    BigInteger res;

    int carry = 0;
    for (size_t i = 0; i < std::max(left.number.size(), right.number.size()) || carry; ++i) {
        if (i == res.number.size()) {
            res.number.push_back(0);
        }
        res.number[i] = left.number[i] + carry + (i < right.number.size() ? right.number[i] : 0);
        carry = res.number[i] >= BigInteger::BASIS;
        if (carry) {
            res.number[i] -= BigInteger::BASIS;
        }
    }
    return res;
}

BigInteger operator-(const BigInteger &left, const BigInteger &right) {
    if (left.isNegative) {
        if (right.isNegative) {
            return left + (-right);
        }
        return -((-left) + right);
    }
    if (right.isNegative) {
        return left + (-right);
    }
    if (left < right) {
        return -(right - left);
    }

    BigInteger res(left);
    int carry = 0;
    for (int i = 0; i < std::max(res.number.size(), right.number.size()) || carry != 0; i++) {
        if (i == res.number.size()) {
            res.number.push_back(0);
        }
        res.number[i] -= (i >= right.number.size() ? 0 : right.number[i]) + carry;
        carry = 0;
        if (res.number[i] < 0) {
            res.number[i] += BigInteger::BASIS;
            carry = 1;
        }
    }
    return res;
}

bool operator<(const BigInteger& left, const BigInteger& right) {
    return !(left > right);
}

bool operator>=(const BigInteger& left, const BigInteger& right) {
    return left > right || left == right;
}

bool operator<=(const BigInteger& left, const BigInteger& right) {
    return left < right || left == right;
}

void BigInteger::rmZero() {
    while (number.size() > 1 && number.back() == 0) {
         number.pop_back();
    }
    if (number.size() == 1 && number[0] == 0) {
        isNegative = 0;
    }
}

BigInteger operator*(const BigInteger& left, const BigInteger& right) {
    BigInteger ans;
    ans.number = std::vector<int>(left.number.size() + right.number.size());
    for (size_t i = 0; i < left.number.size(); ++i)
        for (int j = 0, carry = 0; j < (int)right.number.size() || carry; ++j) {
            long long cur = ans.number[i + j] + left.number[i] * 1ll * (j < (int)right.number.size()
                    ? right.number[j] : 0) + carry;
            ans.number[i+j] = int (cur % BigInteger::BASIS);
            carry = int (cur / BigInteger::BASIS);
        }
    while (ans.number.size() > 1 && ans.number.back() == 0) {
        ans.number.pop_back();
    }
    return ans;
}

BigInteger operator/(const BigInteger& left, const BigInteger& right) {
    BigInteger ans, cur;
    ans.number = std::vector<int>(left.number.size(), 0);
    for (long long i = ans.number.size() - 1; i >= 0; i--) {
        cur.number = std::vector<int>(1, 0);
        cur.number[0] = left.number[i];
        cur.rmZero();
        int l = 0, r = BigInteger::BASIS + 1;
        while (l + 1 != r) {
            int m = (l + r) / 2;
            if (BigInteger(m) * right <= cur) {
                l = m;
            } else {
                r = m;
            }
        }
        ans.number[i] = l;
        cur -= right * BigInteger(l);
    }
    ans.rmZero();
    return ans;
}

BigInteger operator%(const BigInteger& left, const BigInteger& right) {
    if (left.isNegative) {
        return -((-left) % right);
    }
    return left - right * (left / right);
}

BigInteger& BigInteger::operator%=(const BigInteger &num) {
    *this = *this % num;
    return *this;
}

BigInteger& BigInteger::operator/=(const BigInteger &num) {
    *this = *this / num;
    return *this;
}

BigInteger& BigInteger::operator*=(const BigInteger &num) {
    *this = *this * num;
    return *this;
}

BigInteger& BigInteger::operator+=(const BigInteger &num) {
    *this = *this + num;
    return *this;
}

BigInteger& BigInteger::operator-=(const BigInteger &num) {
    *this = *this - num;
    return *this;
}

BigInteger::operator bool() const {
    return !(*this == BigInteger(0));
}

BigInteger& BigInteger::operator++() {
    *this = *this + BigInteger(1);
    return *this;
}

const BigInteger BigInteger::operator++(int) {
    BigInteger tmp = BigInteger(*this);
    *this = *this + BigInteger(1);
    return tmp;
}

BigInteger& BigInteger::operator--() {
    *this = *this - BigInteger(1);
    return *this;
}

const BigInteger BigInteger::operator--(int) {
    BigInteger tmp = BigInteger(*this);
    *this = *this - BigInteger(1);
    return tmp;
}