//
// Created by aidenne on 04/11/2020.
//

#ifndef BIGINTEGER_BIGINTEGER_H
#define BIGINTEGER_BIGINTEGER_H

#include <vector>
#include <iostream>
#include <string>

class BigInteger {

public:
    const static int BASE = 10;

    BigInteger() = default;
    ~BigInteger() = default;

    BigInteger(int num);
    BigInteger(const BigInteger& other);

    BigInteger& operator=(const BigInteger& other);

    friend BigInteger operator+(const BigInteger& b1, const BigInteger& b2);
    friend BigInteger operator-(const BigInteger& b1, const BigInteger& b2);
    friend BigInteger operator*(const BigInteger& b1, const BigInteger& b2);
    friend BigInteger operator/(const BigInteger& b1, const BigInteger& b2);
    friend BigInteger operator%(const BigInteger& b1, const BigInteger& b2);

    BigInteger& operator+=(const BigInteger& b2);
    BigInteger& operator-=(const BigInteger& b2);
    BigInteger& operator*=(const BigInteger& b2);
    BigInteger& operator/=(const BigInteger& b2);
    BigInteger& operator%=(const BigInteger& b2);

    friend BigInteger operator-(const BigInteger& b1);

    //prefix
    BigInteger& operator++();
    BigInteger& operator--();

    //postfix
    BigInteger operator++(int);
    BigInteger operator--(int);

    friend bool operator==(const BigInteger& b1, const BigInteger& b2);
    friend bool operator!=(const BigInteger& b1, const BigInteger& b2);
    friend bool operator<(const BigInteger& b1, const BigInteger& b2);
    friend bool operator>(const BigInteger& b1, const BigInteger& b2);
    friend bool operator<=(const BigInteger& b1, const BigInteger& b2);
    friend bool operator>=(const BigInteger& b1, const BigInteger& b2);

    friend std::ostream& operator<<(std::ostream& out, const BigInteger& b);
    friend std::istream& operator>>(std::istream& in, BigInteger& b);

    std::string toString() const;

    operator int() const;
    operator bool() const;


private:
    std::vector<int> _numbers;

    bool isZero() const;
    bool isNegative() const;
    bool isPositive() const;

    //sgn(b1) == sgn (b2)
    static BigInteger sumWithEqualSigns(const BigInteger& b1, const BigInteger& b2);
    //b1 >=0, b2 < 0
    static BigInteger subtract(const BigInteger& b1, const BigInteger& b2);
    static int compareByModule(const BigInteger& b1, const BigInteger& b2);
    static bool haveEqualSigns(const BigInteger& b1, const BigInteger& b2);

    static BigInteger multStep(const BigInteger& b1, int digit, int zeroes);

};


#endif //BIGINTEGER_BIGINTEGER_H