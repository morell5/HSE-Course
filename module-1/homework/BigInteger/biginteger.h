#pragma once

#include <iostream>
#include <vector>
#include <string>

#define BASE 100000000

class BigInteger
{
public:
    BigInteger();
    BigInteger(int number);

    bool sign() const;
    BigInteger abs() const;
    bool isZero() const;

    BigInteger operator -() const;
    BigInteger& operator ++();
    BigInteger operator ++(int);
    BigInteger& operator --();
    BigInteger operator --(int);

    operator bool() const;
    operator int() const;

    std::string toString() const;

    friend BigInteger intDivide(const BigInteger& lhs, int rhs);
    friend BigInteger& operator +=(BigInteger& lhs, const BigInteger& rhs);
    friend BigInteger& operator *=(BigInteger& lhs, const BigInteger& rhs);
    friend BigInteger& operator /=(BigInteger& lhs, const BigInteger& rhs);
    friend bool operator <(const BigInteger& lhs, const BigInteger& rhs);

private:
    void normalize();

    std::vector<unsigned int> _digits;
    bool _sign = false;
};

bool operator <(const BigInteger& lhs, const BigInteger& rhs);
bool operator >(const BigInteger& lhs, const BigInteger& rhs);
bool operator <=(const BigInteger& lhs, const BigInteger& rhs);
bool operator >=(const BigInteger& lhs, const BigInteger& rhs);
bool operator ==(const BigInteger& lhs, const BigInteger& rhs);
bool operator !=(const BigInteger& lhs, const BigInteger& rhs);

BigInteger intDivide(const BigInteger& lhs, int rhs);

BigInteger operator +(const BigInteger& lhs, const BigInteger& rhs);
BigInteger operator -(const BigInteger& lhs, const BigInteger& rhs);
BigInteger operator *(const BigInteger& lhs, const BigInteger& rhs);
BigInteger operator /(const BigInteger& lhs, const BigInteger& rhs);
BigInteger operator %(const BigInteger& lhs, const BigInteger& rhs);

BigInteger& operator +=(BigInteger& lhs, const BigInteger& rhs);
BigInteger& operator -=(BigInteger& lhs, const BigInteger& rhs);
BigInteger& operator *=(BigInteger& lhs, const BigInteger& rhs);
BigInteger& operator /=(BigInteger& lhs, const BigInteger& rhs);
BigInteger& operator %=(BigInteger& lhs, const BigInteger& rhs);

std::istream& operator >>(std::istream& stream, BigInteger& number);
std::ostream& operator <<(std::ostream& stream, const BigInteger& number);
