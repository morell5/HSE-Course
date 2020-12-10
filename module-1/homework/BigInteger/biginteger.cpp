//
// Created by User on 10.12.2020.
//

#include "biginteger.h"

BigInteger::BigInteger() {
    sign_ = 0;
    nums = std::vector<int>();
}

BigInteger::BigInteger(int n) : BigInteger(static_cast<int64_t>(n)) {}

BigInteger::BigInteger(int64_t n) {
    free();
    if (n == 0) {
        sign_ = 0;
        return;
    } else {
        if (n < 0) {
            sign_ = -1;
            n *= -1;
        } else
            sign_ = 1;
        while (n != 0) {
            nums.emplace_back(n % BASE);
            n /= BASE;
        }
    }
    trim();
}

BigInteger::BigInteger(const std::string &s) {
    sign_ = s[0] == '-' ? -1 : 1;
    int str_size = s.size();
    for (int i = str_size; i > 0; i -= BASE_LEN) {
        std::string chunk = i < BASE_LEN ? s.substr(0, i) : s.substr(i - BASE_LEN, i);
        nums.emplace_back(std::atoi(chunk.c_str()));
    }
    trim();
}

BigInteger &BigInteger::operator=(const BigInteger &) {
    return;
}

BigInteger &BigInteger::operator=(int) {
    return;
}

BigInteger &BigInteger::operator=(const std::string &) {
    return;
}

BigInteger BigInteger::operator+(const BigInteger &) const {
    return BigInteger();
}

BigInteger BigInteger::operator-(const BigInteger &) const {
    return BigInteger();
}

BigInteger BigInteger::operator*(const BigInteger &) const {
    return BigInteger();
}

BigInteger BigInteger::operator/(const BigInteger &) const {
    return BigInteger();
}

BigInteger BigInteger::operator%(const BigInteger &) const {
    return BigInteger();
}

BigInteger BigInteger::operator+=(const BigInteger &) {
    return BigInteger();
}

BigInteger BigInteger::operator-=(const BigInteger &) {
    return BigInteger();
}

BigInteger BigInteger::operator*=(const BigInteger &) {
    return BigInteger();
}

BigInteger BigInteger::operator/=(const BigInteger &) {
    return BigInteger();
}

BigInteger BigInteger::operator%=(const BigInteger &) {
    return BigInteger();
}

BigInteger BigInteger::operator++() {
    return BigInteger();
}

BigInteger BigInteger::operator++(int) {
    return BigInteger();
}

BigInteger BigInteger::operator--() {
    return BigInteger();
}

BigInteger BigInteger::operator--(int) {
    return BigInteger();
}

BigInteger BigInteger::operator-() {
    return BigInteger();
}

BigInteger BigInteger::operator>(const BigInteger &) const {
    return BigInteger();
}

BigInteger BigInteger::operator<(const BigInteger &) const {
    return BigInteger();
}

BigInteger BigInteger::operator>=(const BigInteger &) const {
    return BigInteger();
}

BigInteger BigInteger::operator<=(const BigInteger &) const {
    return BigInteger();
}

BigInteger BigInteger::operator==(const BigInteger &) const {
    return BigInteger();
}

BigInteger BigInteger::operator!=(const BigInteger &) const {
    return BigInteger();
}

BigInteger::operator bool() const {
    return false;
}

std::ostream &operator<<(std::ostream &out, const BigInteger &bi) {
    out << bi.toString();
    return out;
}

std::istream &operator>>(std::istream &in, BigInteger &bi) {
    std::string bi_str;
    in >> bi_str;
    bi = bi_str;
    return in;
}

std::string BigInteger::toString() const {
    std::string result = sign_ == -1 ? "-" : "";
    size_t start = nums.size() - 1;
    while (nums[start] == 0)
        start--;
    for (size_t i = start; i >= 0; i--) {
        std::string chunk = std::to_string(nums[i]);
        for (int j = 0; j < BASE_LEN - chunk.size(); j++)
            result += "0";
        result += chunk;
    }
    return result;
}

void BigInteger::free() {
    nums.clear();
    sign_ = 0;
}

void BigInteger::trim() {
    while (!nums.empty() && nums.back() == 0)
        this->nums.pop_back();

    if (this->nums.empty())
        this->sign_ = 0;
}