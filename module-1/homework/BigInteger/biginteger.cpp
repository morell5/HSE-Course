#include "biginteger.h"
#include <algorithm>

BigInteger::BigInteger() {
    data.push_back(0);
}

BigInteger::BigInteger(std::vector<unsigned char>& data, bool negative) {
    if (data.empty())
        this->data = std::vector<unsigned char>(1);
    else
        this->data = data;
    this->is_negative = negative;
}

BigInteger::BigInteger(const BigInteger& other) {
    std::copy(other.data.begin(), other.data.end(),
                  std::back_inserter(data));
    this->is_negative = other.is_negative;
}

BigInteger::BigInteger(BigInteger&& other) noexcept {
    data = other.data;
    is_negative = other.is_negative;
    other.data = std::vector<unsigned char>();
    other.data.push_back(0);
    other.is_negative = false;
}

BigInteger& BigInteger::operator=(const BigInteger& other) {
    std::copy(other.data.begin(), other.data.end(),
                  std::back_inserter(data));
    this->is_negative = other.is_negative;

    return *this;
}

BigInteger& BigInteger::operator=(BigInteger&& other) noexcept {
    data = other.data;
    is_negative = other.is_negative;
    other.data = std::vector<unsigned char>();
    other.data.push_back(0);
    other.is_negative = false;
    return *this;
}

BigInteger::BigInteger(int num) {
    while (num > 0) {
        data.push_back(num % base);
        num /= base;
    }
}

BigInteger BigInteger::operator-() const {
    BigInteger num(*this);
    num.is_negative = !is_negative;
    return num;
}

BigInteger BigInteger::operator+(const BigInteger& other) const {
    if (is_negative) {
        if (other.is_negative)
            return -(-*this + (-other));
        else
            return (other - (-*this));
    }
    else
        if (other.is_negative)
            return *this - (-other);
    std::vector<unsigned char> new_data;
    std::size_t size = std::max(data.size(), other.data.size());

    unsigned char buffer = 0;
    for (std::size_t i = 0; i < size; ++i) {
        if (i >= data.size()) {
            new_data.push_back(other.data[i] + buffer);
            buffer = 0;
        } else {
            if (i >= other.data.size()) {
                new_data.push_back(data[i] + buffer);
                buffer = 0;
            } else {
                unsigned char sum = data[i] + other.data[i];
                auto elem = (sum + buffer) % base;
                new_data.push_back(elem);

                buffer = (sum + buffer) / base;
            }
        }

    }
    if (buffer > 0)
        new_data.push_back(buffer);

    return BigInteger(new_data);
}

BigInteger BigInteger::operator-(const BigInteger& other) const {
    if (is_negative) {
        if (other.is_negative)
            return other - (-*this);
        else
            return -(-*this + other);
    } else {
        if (other.is_negative)
            return *this + (-other);
    }
    if (*this < other)
        return -(other - *this);

    unsigned char buffer = 0;
    std::vector<unsigned char> new_data;

    for (size_t i = 0; i < data.size(); ++i) {
        if (i >= other.data.size()) {
            if (data[i] < buffer)
                new_data.push_back(base - 1);
            else {
                new_data.push_back(data[i] - buffer);
                buffer = 0;
            }
        } else {
            if (data[i] < other.data[i] + buffer) {
                new_data.push_back(base - other.data[i] - buffer);
                buffer = 1;
            } else {
                new_data.push_back(data[i] - other.data[i] - buffer);
                buffer = 0;
            }
        }
    }

    while ((!new_data.empty()) and new_data.back() == 0)
        new_data.pop_back();

    return BigInteger(new_data);
}

BigInteger& BigInteger::operator+=(const BigInteger &other) {
    return *this = (*this + other);
}

BigInteger& BigInteger::operator-=(const BigInteger &other) {
    return *this = (*this - other);
}

BigInteger& BigInteger::operator++() {
    *this += 1;
    return *this;
}

BigInteger BigInteger::operator++(int) {
    BigInteger tmp(*this);
    operator++();
    return tmp;
}

BigInteger& BigInteger::operator--() {
    *this -= 1;
    return *this;
}

BigInteger BigInteger::operator--(int) {
    BigInteger tmp(*this);
    operator--();
    return tmp;
}

BigInteger BigInteger::operator*(int a) const {
    std::vector<unsigned char> new_data;
    int buffer = 0;
    for (size_t i = 0; i < data.size(); ++i) {
        int prod = data[i] * a + buffer;
        new_data.push_back(prod % base);
        buffer = prod / base;
    }
    while (buffer > 0) {
        new_data.push_back(buffer % base);
        buffer /= base;
    }
    return BigInteger(new_data);
}

BigInteger BigInteger::shift(size_t step) {
    std::vector<unsigned char> new_data(step, 0);
    for (size_t i = 0; i < data.size(); ++i)
        new_data.push_back(data[i]);


    return BigInteger(new_data);
}

BigInteger BigInteger::operator*(const BigInteger &other) const {
    BigInteger output(0);

    for (size_t i = 0; i < other.data.size(); ++i) {
        BigInteger z = (*this * (int)other.data[i]).shift(i);
        output = output + z;
    }

    output.is_negative = is_negative and other.is_negative;
    return output;
}

BigInteger BigInteger::operator/(const BigInteger& other) const { // error in minus operator
    if (*this < other)
        return BigInteger(0);

    std::vector<unsigned char> new_data;

    BigInteger numer = *this;
    BigInteger denom = other;
    BigInteger curden;

    while (numer >= denom) {
        int step = 0;
        if (numer.data.back() < denom.data.back())
            step = 1;

        curden = denom.shift(numer.data.size() - denom.data.size() - step);

        int s = 1;
        while (curden * s <= numer)
            ++s;
        --s;
        new_data.push_back((unsigned int)s);

        numer -= curden * s;
    }

    std::reverse(new_data.begin(), new_data.end());
    bool sign = is_negative and other.is_negative;
    return BigInteger(new_data, sign);
}

BigInteger BigInteger::operator%(const BigInteger &other) const {
    return *this - (*this / other) * other;
}
BigInteger& BigInteger::operator*=(const BigInteger& other) {
    return *this = (*this * other);
}

BigInteger& BigInteger::operator/=(const BigInteger& other) {
    return *this = (*this / other);
}

BigInteger& BigInteger::operator%=(const BigInteger& other) {
    return *this = (*this % other);
}

bool operator==(const BigInteger& lhs, const BigInteger& rhs) {
    if (lhs.data.size() != rhs.data.size())
        return false;
    for (size_t i = 0; i < lhs.data.size(); ++i)
        if (lhs.data[i] != rhs.data[i])
            return false;
    return true;
}

bool operator!=(const BigInteger& lhs, const BigInteger& rhs) {
    return !(lhs == rhs);
}

bool operator<(const BigInteger& lhs, const BigInteger& rhs) {
    if (lhs.data.size() < rhs.data.size())
        return true;
    if (lhs.data.size() > rhs.data.size())
        return false;

    size_t i = lhs.data.size();
    do {
        --i;
        if (lhs.data[i] < rhs.data[i])
            return true;
        if (lhs.data[i] > rhs.data[i])
            return false;
    } while(i != 0);

    return false;
}

bool operator>(const BigInteger& lhs, const BigInteger& rhs) {
    if (lhs.data.size() < rhs.data.size())
        return false;
    if (lhs.data.size() > rhs.data.size())
        return true;

    size_t i = lhs.data.size();
    do {
        --i;
        if (lhs.data[i] > rhs.data[i])
            return true;
        if (lhs.data[i] < rhs.data[i])
            return false;
    } while(i != 0);

    return false;
}

bool operator<=(const BigInteger& lhs, const BigInteger& rhs) {
    return !(lhs > rhs);
}

bool operator>=(const BigInteger& lhs, const BigInteger& rhs) {
    return !(lhs < rhs);
}

std::string BigInteger::toString() const {
    std::string output = "";
    if (is_negative)
        output = "-";
     output += std::to_string(data.back());

    std::string suffix = "";

    size_t i = data.size() - 1;

    if (i == 0)
        return output;

    do {
        i -= 1;
        suffix = "";

        if (data[i] < 10)
            suffix = "0";
        suffix += std::to_string(data[i]);

        output += suffix;

    } while (i != 0);

    return output;
}

std::ostream& operator<<(std::ostream& out, const BigInteger& obj) {
    out << obj.toString();
    return out;
}

std::istream& operator>>(std::istream& in, BigInteger& obj) {
    std::string data;
    in >> data;
    std::string buffer = "";
    std::vector<unsigned char> new_data;

    size_t i = data.size();
    do {
        --i;
        buffer = data[i] + buffer;
        if (i == 0 or buffer.size() == 2) {
            new_data.push_back((unsigned char)std::stoi(buffer));
            buffer = "";
        }
    } while (i != 0);

    obj.data = new_data;

    return in;
}

BigInteger::~BigInteger() {

}

BigInteger::operator bool() const {
    return !(*this == BigInteger(0));
}

