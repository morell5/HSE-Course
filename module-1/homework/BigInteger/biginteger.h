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
    explicit BigInteger(const std::string&);

    BigInteger& operator=(const BigInteger&);
    BigInteger& operator=(int);
    BigInteger& operator=(const std::string&);

    BigInteger operator+(const BigInteger&) const;
    BigInteger operator-(const BigInteger&) const;
    BigInteger operator*(const BigInteger&) const;
    BigInteger operator/(const BigInteger&) const;
    BigInteger operator%(const BigInteger&) const;

    BigInteger operator+=(const BigInteger&);
    BigInteger operator-=(const BigInteger&);
    BigInteger operator*=(const BigInteger&);
    BigInteger operator/=(const BigInteger&);
    BigInteger operator%=(const BigInteger&);

    BigInteger operator++();
    BigInteger operator++(int);
    BigInteger operator--();
    BigInteger operator--(int);

    BigInteger operator-();

    BigInteger operator>(const BigInteger&) const;
    BigInteger operator<(const BigInteger&) const;
    BigInteger operator>=(const BigInteger&) const;
    BigInteger operator<=(const BigInteger&) const;
    BigInteger operator==(const BigInteger&) const;
    BigInteger operator!=(const BigInteger&) const;

    operator bool() const;

    friend std::ostream& operator<<(std::ostream&, const BigInteger&);
    friend std::istream& operator>>(std::istream&, BigInteger&);

    std::string toString() const;

    void free();

private:
    static const int BASE = 1000000;
    static const int BASE_LEN = 6;

    std::vector<int> nums;
    signed char sign_; // 1 if pos, -1 if neg, 0 if zero

    void trim();

};

#endif //BIGINTEGER_BIGINTEGER_H
