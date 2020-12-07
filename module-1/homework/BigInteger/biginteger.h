#pragma once
#ifndef BIGINTEGER_H
#define BIGINTEGER_H

#include <iostream>
#include <vector>
#include <string>

#define LL long long

const LL max_num = 1000000000;

class BigInteger
{

<<<<<<< HEAD
private:
=======
public:

>>>>>>> afb229787fb1876a76394e283821776d41348be4
    std::vector<int> to_vector; // value to vector
    std::string to_string; // value to string
    bool sign = true; // sign before value
    int value = 0; // value for integer

<<<<<<< HEAD
public:


=======
>>>>>>> afb229787fb1876a76394e283821776d41348be4
    std::string toString(); // function to_vector -> to_string
    std::vector<int> toVector(); // function to_string -> to_vector

    BigInteger(const int value);
    BigInteger(const long long value);
    BigInteger();

    operator bool() const;

    BigInteger operator + (BigInteger& number_2);
    BigInteger operator - (BigInteger& number_2);
    BigInteger operator * (BigInteger& number_2);
    BigInteger operator / (BigInteger& number_2);
    BigInteger operator % (BigInteger& number_2);
    BigInteger& operator += (BigInteger number_2);
    BigInteger& operator -= (BigInteger number_2);
    BigInteger& operator *= (BigInteger number_2);
    BigInteger& operator /= (BigInteger number_2);
    BigInteger& operator %= (BigInteger number_2);

    BigInteger& operator = (const int& number_int); // convert int to BigInteger
    BigInteger& operator = (const long long& number_int); // convert long long to BigInteger

    const bool operator < (const BigInteger& number_2);
    const bool operator > (const BigInteger& number_2);
    const bool operator == (const BigInteger& number_2);
    const bool operator <= (const BigInteger& number_2);
    const bool operator >= (const BigInteger& number_2);
    const bool operator != (const BigInteger& number_2);

    BigInteger& operator ++ ();
    BigInteger operator ++ (int);
    BigInteger& operator -- ();
    BigInteger operator -- (int);
    BigInteger& operator - ();


    BigInteger operator + (const int& Const);
    BigInteger operator - (const int& Const);
    BigInteger operator * (const int& Const);
    BigInteger operator / (const int& Const);
    BigInteger operator % (const int& Const);
    BigInteger operator += (const int& Const);
    BigInteger operator -= (const int& Const);
    BigInteger operator *= (const int& Const);
    BigInteger operator /= (const int& Const);
    BigInteger operator %= (const int& Const);
<<<<<<< HEAD
    friend std::ostream& operator << (std::ostream& out, const BigInteger& number);
    friend std::istream& operator >> (std::istream& in, BigInteger& number);
=======
>>>>>>> afb229787fb1876a76394e283821776d41348be4
};

std::ostream& operator << (std::ostream& out, const BigInteger& number);
std::istream& operator >> (std::istream& in, BigInteger& number);

#endif

