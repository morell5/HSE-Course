#include "biginteger.h"

BigInteger::operator int() const {
    int res = 0;
    int mult = 1;
    for (size_t i = 1; i < _digits->size(); ++i) {
        res += (*_digits)[i] * mult;
        mult *= BASE;
    }
    if ((*_digits)[0]) {
        res = -res;
    }
    return res;
}

BigInteger::operator bool() const {
    return int(*this) != 0;
}

BigInteger& BigInteger::operator=(const BigInteger &other) {
    _digits->clear();
    if (other._digits) {
        for (int el: *other._digits) {
            _digits->push_back(el);
        }
    }
    return *this;
}

BigInteger BigInteger::operator-() {
    BigInteger res(*this);
    (*res._digits)[0] = !(*_digits)[0];
    return res;
}

// --------- comparison operators ------------

bool BigInteger::operator==(const BigInteger& other) const {
    if (_digits->size() != other._digits->size()) {
        return false;
    }

    int len = _digits->size();
    for (size_t i = 0; i < len; ++i) {
        if ((*_digits)[i] != (*other._digits)[i]) {
            return false;
        }
    }
    return true;
}

bool BigInteger::operator!=(const BigInteger &other) const {
    return !(*this == other);
}

bool BigInteger::operator<=(const BigInteger& other) const{
    if (isPositive() && !other.isPositive()) {
        return false;
    }

    if (!isPositive() && other.isPositive()) {
        return true;
    }

    int greaterByModulus = compareModulus(other);
    switch (greaterByModulus) {
        case 0:
            return true;
        case 1:
            return !isPositive();
        case -1:
            return isPositive();
    }
}

bool BigInteger::operator>=(const BigInteger& other) const{
    // this number is positive and other is negative
    if ((*_digits)[0] == 0 && (*other._digits)[0] == 1) {
        return true;
    }

    // this number is negative and other is positive
    if ((*_digits)[0] == 1 && (*other._digits)[0] == 0) {
        return false;
    }

    int greaterByModulus = compareModulus(other);
    if (greaterByModulus == 0) {
        return true;
    }

    switch (greaterByModulus) {
        case 1:
            if (isPositive()) return true;
            return false;
        case -1:
            if (isPositive()) return false;
            return true;
    }
}

bool BigInteger::operator>(const BigInteger &other) const {
    return *this >= other && *this != other;
    // return !(*this < other);
}

bool BigInteger::operator<(const BigInteger &other) const {
    return *this <= other && *this != other;
}

//------------ arithmetic operators ---------------

BigInteger operator+(const BigInteger &lhs, const BigInteger &rhs) {

    if (lhs.isPositive() && rhs.isPositive()) {
        return BigInteger::sum(lhs, rhs, 0);
    }

    if (!lhs.isPositive() && !rhs.isPositive()) {
        return BigInteger::sum(lhs, rhs, 1);
    }

    if (lhs.isPositive() && !rhs.isPositive()) {
        if (lhs.compareModulus(rhs) > 0) {
            return BigInteger::substract(lhs, rhs, 0);
        }
        return BigInteger::substract(rhs, lhs, 1);
    }

    if (lhs.compareModulus(rhs) > 0) {
        return BigInteger::substract(lhs, rhs, 1);
    }
    return BigInteger::substract(rhs, lhs, 0);
}

BigInteger operator-(const BigInteger& lhs, const BigInteger& rhs) {
    if (lhs.isPositive() && rhs.isPositive()) {
        if (lhs.compareModulus(rhs) > 0) {
            return BigInteger::substract(lhs, rhs, 0);
        }
        return BigInteger::substract(rhs, lhs, 1);
    }

    if (!lhs.isPositive() && !rhs.isPositive()) {
        if (lhs.compareModulus(rhs) > 0) {
            return BigInteger::substract(lhs, rhs, 1);
        }
        return BigInteger::substract(rhs, lhs, 0);
    }

    if (lhs.isPositive() && !rhs.isPositive()) {
        return BigInteger::sum(lhs, rhs, 0);
    }

    return BigInteger::sum(lhs, rhs, 1);
}

BigInteger operator*(const BigInteger& lhs, const BigInteger& rhs) {
    int times = (int)rhs;
    if (times < 0) {
        times = -times;
    }
    BigInteger res(lhs);
    for (int i = 0; i < times - 1; ++i) {
        res = BigInteger::sum(res, lhs, 0);
    }
    (*res._digits)[0] = ((*lhs._digits)[0] + (*rhs._digits)[0]) % 2;
    return res;
}

BigInteger operator/(const BigInteger& lhs, const BigInteger& rhs) {
    if (lhs < rhs) {
        return 0;
    }
    int times = 0;
    BigInteger tmp = lhs;
    while (tmp >= rhs) {
        tmp -= rhs;
        ++times;
    }
    return times;
}

BigInteger operator%(const BigInteger &lhs, const BigInteger &rhs) {
    BigInteger tmp = lhs;
    while (tmp >= rhs) {
        tmp -= rhs;
    }
    return tmp;
}

// ------------ compound assignment operators ----------------

BigInteger& BigInteger::operator+=(const BigInteger& other) {
    *this = *this + other;
    return *this;
}

BigInteger& BigInteger::operator-=(const BigInteger& other) {
    *this = *this - other;
    return *this;
}

BigInteger& BigInteger::operator*=(const BigInteger& other) {
    *this = *this * other;
    return *this;
}

BigInteger& BigInteger::operator/=(const BigInteger& other) {
    *this = *this / other;
    return *this;
}

BigInteger& BigInteger::operator%=(const BigInteger& other) {
    *this = *this % other;
    return *this;
}

// ----------- increment/decrement --------------

BigInteger& BigInteger::operator++() {
    *this += 1;
    return *this;
}

BigInteger BigInteger::operator++(int) {
    BigInteger tmp = *this;
    *this += 1;
    return tmp;
}

BigInteger& BigInteger::operator--() {
    *this -= 1;
    return *this;
}

BigInteger BigInteger::operator--(int) {
    BigInteger tmp = *this;
    *this -= 1;
    return tmp;
}

// ------------- I/O ---------------

std::ostream& operator<<(std::ostream& output, const BigInteger& num) {
    std::vector<int> digits = *num._digits;
    if (digits.size() == 1) {
        if (digits[0] == 0) {
            output << digits[0];
            return output;
        }
        throw std::invalid_argument("Big integer of length 1 must be a zero");
    }
    if (digits[0]) {
        output << "-";
    }
    for (int i = digits.size() - 1; i > 0; --i) {
        output << digits[i];
    }
    return output;
}

std::istream& operator>>(std::istream& input, BigInteger& num) {
    std::string data;
    input >> data;

    if (num._digits) {
        delete num._digits;
        num._digits = new std::vector<int>();
    }

    if (data.length() == 1) {
        if (data[0] == '0') {
            num._digits->push_back(0);
            return input;
        }
        throw std::invalid_argument("Big integer of length 1 must be a zero");
    }

    if (data[0] == '-') {
        num._digits->push_back(1);
    } else {
        num._digits->push_back(0);
    }

    for (int i = data.length() - 1; i >= 0; --i) {
        if (data[i] == '-') {
            continue;
        }
        num._digits->push_back(data[i] - '0');
    }
    return input;
}

std::string BigInteger::toString() {
    std::string outstr = "";
    if ((*_digits)[0]) {
        outstr += "-";
    }
    for (size_t i = _digits->size() - 1; i > 0; --i) {
        outstr += std::to_string((*_digits)[i]);
    }
    return outstr;
}

// ---------- private helper methods -----------------

int BigInteger::compareModulus(const BigInteger &other) const {
    if (_digits->size() > other._digits->size()) {
        return 1;
    }

    if (_digits->size() < other._digits->size()) {
        return -1;
    }

    if (*this == other) {
        return 0;
    }

    int len = _digits->size();
    for (size_t i = len - 1; i > 0; --i) {
        if ((*_digits)[i] == (*other._digits)[i]) {
            continue;
        }
        if ((*_digits)[i] > (*other._digits)[i]) {
            return 1;
        }
        if ((*_digits)[i] < (*other._digits)[i]) {
            return -1;
        }
    }

    return 0;
}

bool BigInteger::isPositive() const {
    return (*_digits)[0] == 0;
}

BigInteger BigInteger::sum(const BigInteger& lhs, const BigInteger& rhs, bool sign) {
    BigInteger res;
    // this helper method is for summing positive numbers, so the sign is +
    res._digits->push_back(sign);
    int len = std::max(lhs._digits->size(), rhs._digits->size());
    bool extra = false;
    for (size_t i = 1; i < len; ++i) {
        int summand1 = 0, summand2 = 0;
        if (i < lhs._digits->size()) {
            summand1 = (*lhs._digits)[i];
        }
        if (i < rhs._digits->size()) {
            summand2 = (*rhs._digits)[i];
        }
        int currSum = summand1 + summand2 + extra;
        if (currSum >= BASE) {
            extra = true;
            res._digits->push_back(currSum % BASE);
        } else {
            extra = false;
            res._digits->push_back(currSum);
        }
    }

    if (extra) {
        res._digits->push_back(1);
    }
    return res;
}

// treats numbers as positive, assumes that the first argument is greater than the second
BigInteger BigInteger::substract(const BigInteger& lhs, const BigInteger& rhs, bool sign) {
    BigInteger res;
    if (lhs == rhs) {
        res._digits->push_back(0);
        return res;
    }

    res._digits->push_back(sign);
    int len = lhs._digits->size();
    bool extra = false;
    for (size_t i = 1; i < len; ++i) {
        int minuend = (*lhs._digits)[i];
        int subtrahend = 0;
        if (i < rhs._digits->size()) {
            subtrahend = (*rhs._digits)[i];
        }
        int currDiff = minuend - subtrahend - extra;
        if (currDiff < 0) {
            extra = true;
            res._digits->push_back(currDiff + BASE);
        } else {
            extra = false;
            res._digits->push_back(currDiff);
        }
    }


    while (res._digits->back() == 0) {
        res._digits->pop_back();
    }

    if (res._digits->size() == 1) {
        (*res._digits)[0] = 0;
    }
    return res;
}
