#include "biginteger.h"

BigInteger::BigInteger()
    : _digits(1)
{ }

BigInteger::BigInteger(int number)
{
    _sign = number < 0;
    number = std::abs(number);

    do {
        _digits.push_back(number % BASE);
        number /= BASE;
    } while (number > 0);
}

bool BigInteger::sign() const
{
    return _sign;
}

BigInteger BigInteger::abs() const
{
    return this->sign() ? -*this : *this;
}

bool BigInteger::isZero() const
{
    return _digits.size() == 1 && _digits[0] == 0;
}

BigInteger BigInteger::operator -() const
{
    BigInteger other(*this);
    if (!other.isZero())
        other._sign = !_sign;

    return other;
}

BigInteger& BigInteger::operator ++()
{
    return *this += 1;
}

BigInteger BigInteger::operator ++(int)
{
    BigInteger other(*this);
    *this += 1;
    return other;
}

BigInteger& BigInteger::operator --()
{
    return *this -= 1;
}

BigInteger BigInteger::operator --(int)
{
    BigInteger other(*this);
    *this -= 1;
    return other;
}

BigInteger::operator bool() const
{
    return !isZero();
}

BigInteger::operator int() const
{
    int result = 0;
    int power = 1;

    for (size_t i = 0; i < _digits.size(); ++i) {
        result += _digits[i] * power;
        power *= BASE;
    }

    return _sign ? -result : result;
}

std::string BigInteger::toString() const
{
    std::string result;
    BigInteger number(this->abs());

    do {
        BigInteger divided = intDivide(number, 10);

        int digit = std::abs(int(number - divided * BigInteger(10)));

        result += std::to_string(digit);
        number = std::move(divided);
    } while (number);

    if (_sign)
        result += "-";

    for (size_t i = 0; i < result.size() / 2; ++i)
        std::swap(result[i], result[result.size() - i - 1]);

    return result;
}

void BigInteger::normalize()
{
    while (_digits.size() > 1 && _digits.back() == 0)
        _digits.erase(_digits.end() - 1);

    if (isZero())
        _sign = 0;
}

bool operator <(const BigInteger& lhs, const BigInteger& rhs)
{
    if (lhs.isZero() && rhs.isZero())
        return false;

    bool invert = false;
    if (lhs._sign && rhs._sign)
        invert = true;
    else if (lhs._sign)
        return true;
    else if (rhs._sign)
        return false;

    int llast = lhs._digits.size() - 1;
    while (llast > 0 && lhs._digits[llast] == 0)
        --llast;

    int rlast = rhs._digits.size() - 1;
    while (rlast > 0 && rhs._digits[rlast] == 0)
        --rlast;

    if (llast != rlast)
        return (llast < rlast) ^ invert;

    while (llast >= 0) {
        if (lhs._digits[llast] != rhs._digits[llast])
            return (lhs._digits[llast] < rhs._digits[llast]) ^ invert;
        --llast;
    }

    return invert;
}

bool operator >(const BigInteger& lhs, const BigInteger& rhs)
{
    return !(lhs <= rhs);
}

bool operator <=(const BigInteger& lhs, const BigInteger& rhs)
{
    return lhs < rhs || lhs == rhs;
}

bool operator >=(const BigInteger& lhs, const BigInteger& rhs)
{
    return !(lhs < rhs);
}

bool operator ==(const BigInteger& lhs, const BigInteger& rhs)
{
    return !(lhs < rhs) && !(rhs < lhs);
}

bool operator !=(const BigInteger& lhs, const BigInteger& rhs)
{
    return !(lhs == rhs);
}

BigInteger intDivide(const BigInteger& lhs, int rhs)
{
    if (rhs == 0)
        throw std::invalid_argument("Divide by zero");

    std::vector<unsigned int> digits;
    bool sign = lhs.sign() ^ (rhs < 0);
    rhs = std::abs(rhs);

    unsigned long long reminder = 0;
    for (int i = lhs._digits.size() - 1; i >= 0; --i) {
        reminder *= BASE;
        reminder += lhs._digits[i];
        if (digits.size() == 0 && reminder < static_cast<unsigned long long>(rhs) && i != 0)
            continue;
        digits.push_back(reminder / rhs);
        reminder -= digits.back() * rhs;
    }

    for (size_t i = 0; i < digits.size() / 2; ++i)
        std::swap(digits[i], digits[digits.size() - i - 1]);

    BigInteger res;
    res._sign = sign;
    res._digits = std::move(digits);
    res.normalize();
    return res;
}

BigInteger operator +(const BigInteger& lhs, const BigInteger& rhs)
{
    BigInteger res(lhs);
    res += rhs;
    return res;
}

BigInteger operator -(const BigInteger& lhs, const BigInteger& rhs)
{
    BigInteger res(lhs);
    res -= rhs;
    return res;
}

BigInteger operator *(const BigInteger& lhs, const BigInteger& rhs)
{
    BigInteger res(lhs);
    res *= rhs;
    return res;
}

BigInteger operator /(const BigInteger& lhs, const BigInteger& rhs)
{
    BigInteger res(lhs);
    res /= rhs;
    return res;
}

BigInteger operator %(const BigInteger& lhs, const BigInteger& rhs)
{
    BigInteger res(lhs);
    res %= rhs;
    return res;
}

BigInteger& operator +=(BigInteger& lhs, const BigInteger& rhs)
{
    if (!lhs.sign() && !rhs.sign()) {
        unsigned long long remainder = 0;
        size_t i = 0;
        do {
            if (i == lhs._digits.size())
                lhs._digits.push_back(0);

            remainder += lhs._digits[i];
            if (i < rhs._digits.size())
                remainder += rhs._digits[i];

            lhs._digits[i] = remainder % BASE;
            remainder -= lhs._digits[i];

            ++i;
            remainder /= BASE;
        } while (remainder > 0 || i < rhs._digits.size());
    } else if (lhs.sign() && rhs.sign()) {
        lhs = -(-lhs + -rhs);
    } else if (lhs.sign()) {
        lhs = rhs + lhs;
    } else if (rhs.abs() > lhs.abs()) {
        lhs = -(rhs.abs() - lhs.abs());
    } else {
        for (size_t i = 0; i < rhs._digits.size(); ++i) {
            if (lhs._digits[i] >= rhs._digits[i]) {
                lhs._digits[i] -= rhs._digits[i];
            } else {
                size_t j = i + 1;
                while (lhs._digits[j] == 0)
                    ++j;
                --lhs._digits[j];
                lhs._digits[i] += BASE - rhs._digits[i];
            }
        }
    }

    lhs.normalize();
    return lhs;
}

BigInteger& operator -=(BigInteger& lhs, const BigInteger& rhs)
{
    BigInteger neg = -rhs;
    return lhs += neg;
}

BigInteger& operator *=(BigInteger& lhs, const BigInteger& rhs)
{
    BigInteger labs = lhs.abs();
    BigInteger rabs = rhs.abs();
    bool sign = lhs.sign() ^ rhs.sign();
    lhs = 0;

    for (size_t i = 0; i < rabs._digits.size(); ++i) {
        BigInteger cur = labs;

        unsigned long long remainder = 0;
        size_t j = 0;
        do {
            if (j == cur._digits.size())
                cur._digits.push_back(0);

            remainder += static_cast<unsigned long long>(cur._digits[j]) * rabs._digits[i];
            cur._digits[j] = remainder % BASE;
            remainder -= cur._digits[j];

            ++j;
            remainder /= BASE;
        } while (remainder > 0 || j < labs._digits.size());

        std::vector<unsigned int> digits(i);
        digits.insert(digits.end(), cur._digits.begin(), cur._digits.end());
        cur._digits = std::move(digits);

        lhs += cur;
    }

    if (sign)
        lhs = -lhs;

    lhs.normalize();
    return lhs;
}

BigInteger& operator /=(BigInteger& lhs, const BigInteger& rhs)
{
    if (rhs.isZero())
        throw std::invalid_argument("Divide by zero");

    BigInteger labs = lhs.abs();
    BigInteger rabs = rhs.abs();
    bool sign = lhs.sign() ^ rhs.sign();
    lhs = 0;

    if (labs.isZero() || labs < rabs) {
        lhs = BigInteger(0);
        return lhs;
    }

    BigInteger left = 1;
    BigInteger right = labs;

    while (left != right) {
        lhs = left + intDivide(right - left + BigInteger(1), 2);

        if (lhs * rabs <= labs)
            left = lhs;
        else
            right = lhs - BigInteger(1);
    }

    lhs = sign ? -left : left;

    lhs.normalize();
    return lhs;
}

BigInteger& operator %=(BigInteger& lhs, const BigInteger& rhs)
{
    BigInteger div = lhs / rhs;
    lhs -= div * rhs;
    return lhs;
}

std::istream& operator >>(std::istream& stream, BigInteger& number)
{
    while (stream.peek() == ' ' || stream.peek() == '\n')
        stream.get();

    number = 0;

    bool sign = false;
    if (!stream.eof() && stream.peek() == '-') {
        sign = true;
        stream.get();
    }

    bool read = false;
    while (!stream.eof() && stream.peek() >= '0' && stream.peek() <= '9') {
        read = true;
        number *= 10;
        number += stream.get() - '0';
    }

    if (!read)
        throw std::invalid_argument("Can't read number");

    if (sign)
        number = -number;

    return stream;
}

std::ostream& operator <<(std::ostream& stream, const BigInteger& number)
{
    stream << number.toString();
    return stream;
}
