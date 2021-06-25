#pragma once

#include <iostream>
#include <string>
#include <vector>


class BigInteger {
public:
    static const int BASIS = 1000 * 1000 * 1000;

    BigInteger (int integer);
    BigInteger (std::string num);
    BigInteger (bool negativity, std::vector<int> num) : number(std::move(num)), isNegative(negativity) {};
    BigInteger (const BigInteger& cur) : isNegative(cur.isNegative), number(cur.number){};
    BigInteger() = default;
    std::string toString() const;

    friend std::ostream& operator<<(std::ostream &out, const BigInteger &num);
    friend std::istream& operator>>(std::istream &in, BigInteger &num);

    friend BigInteger operator+(const BigInteger& left, const BigInteger& right);
    friend BigInteger operator-(const BigInteger& left, const BigInteger& right);
    friend BigInteger operator/(const BigInteger& left, const BigInteger& right);
    friend BigInteger operator*(const BigInteger& left, const BigInteger& right);
    friend BigInteger operator%(const BigInteger& left, const BigInteger& right);
    friend bool operator==(const BigInteger& left, const BigInteger& right);
    friend bool operator>(const BigInteger& left, const BigInteger& right);
    friend bool operator<(const BigInteger& left, const BigInteger& right);
    friend bool operator>=(const BigInteger& left, const BigInteger& right);
    friend bool operator<=(const BigInteger& left, const BigInteger& right);


    BigInteger& operator=(const BigInteger& num);
    BigInteger& operator=(const int num);
    BigInteger& operator+=(const BigInteger& num);
    BigInteger& operator-=(const BigInteger& num);
    BigInteger& operator*=(const BigInteger& num);
    BigInteger& operator/=(const BigInteger& num);
    BigInteger& operator%=(const BigInteger& num);

    BigInteger& operator++();
    const BigInteger operator++(int);
    BigInteger& operator--();
    const BigInteger operator--(int);
    const BigInteger operator-() const;

    operator bool() const;
private:
    void rmZero();

    bool isNegative = false;
    std::vector<int> number;

    void convertNum(std::vector<int>& number, std::string& strNum);
};

