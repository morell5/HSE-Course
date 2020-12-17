//
// Created by User on 10.12.2020.
//

#ifndef BIGINTEGER_BIGINTEGER_H
#define BIGINTEGER_BIGINTEGER_H

#include <string>
#include <vector>
#include <iostream>

class BigInteger {
public:
    BigInteger();

    BigInteger(int);

    BigInteger(int64_t);

    explicit BigInteger(const std::string &);

    BigInteger &operator=(const BigInteger &);

    BigInteger &operator=(int);

    BigInteger &operator=(int64_t);

    BigInteger &operator=(const std::string &);

    BigInteger operator+(const BigInteger &) const;

    BigInteger operator-(const BigInteger &) const;

    BigInteger operator*(const BigInteger &) const;

    BigInteger operator/(const BigInteger &) const;

    BigInteger operator/(int) const;

    BigInteger operator%(const BigInteger &) const;

    BigInteger operator+=(const BigInteger &);

    BigInteger operator-=(const BigInteger &);

    BigInteger operator*=(const BigInteger &);

    BigInteger operator/=(const BigInteger &);

    BigInteger operator/=(int);

    BigInteger operator%=(const BigInteger &);

    BigInteger operator++();

    BigInteger operator++(int);

    BigInteger operator--();

    BigInteger operator--(int);

    BigInteger operator-() const;

    BigInteger operator>(const BigInteger &) const;

    BigInteger operator<(const BigInteger &) const;

    BigInteger operator>=(const BigInteger &) const;

    BigInteger operator<=(const BigInteger &) const;

    BigInteger operator==(const BigInteger &) const;

    BigInteger operator!=(const BigInteger &) const;

    operator bool() const;

    friend std::ostream &operator<<(std::ostream &, const BigInteger &);

    friend std::istream &operator>>(std::istream &, BigInteger &);

    friend BigInteger abs(const BigInteger &);

    std::string toString() const;

private:
    static const int BASE = 1000000;
    static const int BASE_LEN = 6;

    std::vector<int> nums;
    bool sign_; // true if neg, else false

    void trim();

    int getNum(int) const;

    BigInteger &plus(const BigInteger &, bool);
};

#endif //BIGINTEGER_BIGINTEGER_H
