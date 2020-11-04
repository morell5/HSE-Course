//
// Created by aidenne on 04/11/2020.
//

#include "biginteger.h"


BigInteger::BigInteger(int num) {
    if (num == 0) {
        _numbers.push_back(0);
        return;
    }
    _numbers.push_back(num < 0);
    num = num < 0 ? -num : num;

    while (num > 0) {
        _numbers.push_back(num % BASE);
        num /= BASE;
    }
}

BigInteger::BigInteger(const BigInteger& other) {
    for (int num : other._numbers) {
        _numbers.push_back(num);
    }
}

BigInteger& BigInteger::operator=(const BigInteger& other) {
    _numbers.clear();

    for (int num : other._numbers) {
        _numbers.push_back(num);
    }

    return *this;
}

BigInteger operator-(const BigInteger& b1) {
    BigInteger negated(b1);
    if (b1.isZero()) {
        return negated;
    }
    negated._numbers[0] = !b1._numbers[0];
    return negated;
}

BigInteger operator+(const BigInteger& b1, const BigInteger& b2) {
    if (b1.isZero())
        return BigInteger(b2);
    if (b2.isZero())
        return BigInteger(b1);

    if (BigInteger::haveEqualSigns(b1, b2))
        return BigInteger::sumWithEqualSigns(b1, b2);
    if (b1.isNegative())
        return BigInteger::subtract(b2, b1);
    else
        return BigInteger::subtract(b1, b2);
}

BigInteger operator-(const BigInteger& b1, const BigInteger& b2) {
    const BigInteger negated = -b2;
    return b1 + negated;
}

BigInteger operator*(const BigInteger& b1, const BigInteger& b2) {
    if (b1.isZero() || b2.isZero())
        return BigInteger(0);
    bool sign = !BigInteger::haveEqualSigns(b1, b2);
    BigInteger mult(0);
    for (size_t i = 1; i < b2._numbers.size(); i++) {
        mult = mult + BigInteger::multStep(b1, b2._numbers[i], i - 1);
    }
    mult._numbers[0] = sign;
    return mult;
}

BigInteger operator/(const BigInteger& b1, const BigInteger& b2) {
    if (b2.isZero())
        throw std::runtime_error("division  by zero");
    if (b1 < b2 || b1.isZero())
        return 0;

    BigInteger pos_b2(b2);
    pos_b2._numbers[0] = 0;

    BigInteger counter(0);
    BigInteger cur(b1);
    cur._numbers[0] = 0;
    while (cur >= pos_b2) {
        cur = cur - pos_b2;
        counter += 1;
    }

    return counter;
}

BigInteger operator%(const BigInteger& b1, const BigInteger& b2) {
    if (b2.isZero())
        throw std::runtime_error("division  by zero");
    BigInteger pos_b2(b2);
    pos_b2._numbers[0] = 0;

    BigInteger cur(b1);
    cur._numbers[0] = 0;

    while (cur >= pos_b2)
        cur = cur - pos_b2;

    return cur;
}

bool operator==(const BigInteger& b1, const BigInteger& b2) {
    if (b1._numbers.size() != b2._numbers.size()) {
        return false;
    }

    for (size_t i = 0; i < b1._numbers.size(); i++) {
        if (b1._numbers[i] != b2._numbers[i])
            return false;
    }
    return true;
}

bool operator!=(const BigInteger& b1, const BigInteger& b2) {
    return !(b1 == b2);
}

bool operator<(const BigInteger& b1, const BigInteger& b2) {
    return (b1.isNegative() && !b2.isNegative())
           || (BigInteger::haveEqualSigns(b1, b2) && BigInteger::compareByModule(b1, b2) < 0)
           || (b1.isZero() && b2.isPositive());
}

bool operator>(const BigInteger& b1, const BigInteger& b2) {
    return (b1.isPositive() && !b2.isPositive())
           || (BigInteger::haveEqualSigns(b1, b2) && BigInteger::compareByModule(b1, b2) > 0)
           || (b1.isZero() && b2.isNegative());
}

bool operator<=(const BigInteger& b1, const BigInteger& b2) {
    return b1 < b2 || b1 == b2;
}

bool operator>=(const BigInteger& b1, const BigInteger& b2) {
    return b1 > b2 || b1 == b2;
}

BigInteger& BigInteger::operator+=(const BigInteger& b2) {
    *this = *this + b2;
    return *this;
}

BigInteger& BigInteger::operator-=(const BigInteger& b2) {
    *this = *this - b2;
    return *this;
}

BigInteger& BigInteger::operator*=(const BigInteger& b2) {
    *this = *this * b2;
    return *this;
}

BigInteger& BigInteger::operator/=(const BigInteger& b2) {
    *this = *this / b2;
    return *this;
}

BigInteger& BigInteger::operator%=(const BigInteger& b2) {
    *this = *this % b2;
    return *this;
}

BigInteger& BigInteger::operator++() {
    *this += 1;
    return *this;
}

BigInteger BigInteger::operator++(int) {
    BigInteger res(*this);
    *this += 1;
    return res;
}

BigInteger& BigInteger::operator--() {
    *this -= 1;
    return *this;
}

BigInteger BigInteger::operator--(int) {
    BigInteger res(*this);
    *this -= 1;
    return res;
}

std::string BigInteger::toString() const {
    if (isZero())
        return "0";

    std::string res = _numbers[0] ? "-" : "";

    for (size_t i = _numbers.size() - 1; i > 0; i--)
        res += std::to_string(_numbers[i]);

    return res;
}

std::ostream& operator<<(std::ostream& out, const BigInteger& b) {
    out << b.toString();
    return out;
}

std::istream& operator>>(std::istream& in, BigInteger& b) {
    std::string data;
    in >> data;
    b._numbers.clear();

    if (data.length() == 1) {
        if (data[0] == '0') {
            b._numbers.push_back(0);
            return in;
        }
        throw std::invalid_argument("Big integer of length 1 must be a zero");
    }
    int pos = 0;
    char sign = data[0];
    if (sign == '-') {
        b._numbers.push_back(1);
        pos++;
    } else
        b._numbers.push_back(0);

    for (int i = data.length() - 1; i >= pos; i--) {
        b._numbers.push_back(data[i] - '0');
    }
    return in;
}

BigInteger::operator int() const {
    int res = 0;
    int multiplier = 1;

    for (size_t i = 1; i < _numbers.size(); i++) {
        res += _numbers[i] * multiplier;
        multiplier *= BASE;
    }

    return _numbers[0] ? -res : res;
}

BigInteger::operator bool() const {
    return int(*this) != 0;
}

BigInteger BigInteger::subtract(const BigInteger& b1, const BigInteger& b2) {

    int compareModulesResult = BigInteger::compareByModule(b1, b2);

    //true because b2 <= 0, b1 >= 0
    if (compareModulesResult == 0)
        return BigInteger(0);

    const BigInteger* biggerByModule = compareModulesResult > -1 ? &b1 : &b2;
    const BigInteger* smallerByModule = *biggerByModule == b1 ? &b2 : &b1;

    BigInteger dif(0);
    dif._numbers[0] = *biggerByModule == b1 ? 0 : 1;

    int curDif = 0;
    for (size_t i = 1; i < biggerByModule->_numbers.size(); i++) {
        curDif = biggerByModule->_numbers[i] - curDif;
        if (i < smallerByModule->_numbers.size())
            curDif -= smallerByModule->_numbers[i];
        if (curDif < 0)
            dif._numbers.push_back(curDif + BASE);
        else
            dif._numbers.push_back(curDif);
        curDif = curDif < 0;
    }

    while (dif._numbers[dif._numbers.size() - 1] == 0)
        dif._numbers.pop_back();

    return dif;
}

BigInteger BigInteger::sumWithEqualSigns(const BigInteger& b1, const BigInteger& b2) {

    int curSum = 0;
    const BigInteger* bigger = b1._numbers.size() > b2._numbers.size() ? &b1 : &b2;
    const BigInteger* smaller = *bigger == b1 ? &b2 : &b1;

    BigInteger sum(*bigger);
    for (size_t i = 1; i < bigger->_numbers.size(); i++) {

        curSum = curSum + bigger->_numbers[i];
        if (i < smaller->_numbers.size())
            curSum += smaller->_numbers[i];

        sum._numbers[i] = curSum % BASE;
        curSum /= BASE;
    }

    if (curSum > 0)
        sum._numbers.push_back(curSum);
    return sum;
}

bool BigInteger::isZero() const {
    return _numbers.size() == 1 && _numbers[0] == 0;
}

bool BigInteger::isPositive() const {
    return !isZero() && _numbers[0] == 0;
}

bool BigInteger::isNegative() const {
    return !isZero() && _numbers[0] == 1;
}

int BigInteger::compareByModule(const BigInteger& b1, const BigInteger& b2) {
    if (b1._numbers.size() > b2._numbers.size()) {
        return 1;
    }

    if (b1._numbers.size() < b2._numbers.size()) {
        return -1;
    }

    for (size_t i = b1._numbers.size() - 1; i > 0; i--) {
        if (b1._numbers[i] > b2._numbers[i])
            return 1;
        if (b1._numbers[i] < b2._numbers[i])
            return -1;
    }

    return 0;
}

bool BigInteger::haveEqualSigns(const BigInteger& b1, const BigInteger& b2) {
    return (b1.isZero() && b2.isZero()) || (b1.isPositive() == b2.isPositive());
}

BigInteger BigInteger::multStep(const BigInteger& b1, int digit, int zeroes) {
    int curSum = 0;
    BigInteger mult(0);

    for (int i = 0; i < zeroes; i++)
        mult._numbers.push_back(0);

    for (size_t i = 1; i < b1._numbers.size(); i++) {
        curSum += digit * b1._numbers[i];
        mult._numbers.push_back(curSum % BASE);
        curSum /= BASE;
    }

    if (curSum != 0)
        mult._numbers.push_back(curSum);

    return mult;
}