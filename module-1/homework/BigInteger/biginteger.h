//
// Created by kimigaev on 21.09.2020.
//

#ifndef BIGINTEGER_BIGINTEGER_H
#define BIGINTEGER_BIGINTEGER_H

#include <vector>
#include <iostream>
#include <string>

class BigInteger {

  int32_t sign_ = 1;
  static const uint32_t MAX = 1000000000;
  std::vector<uint32_t> data_ = {0};

  static uint32_t vector_at(std::vector<uint32_t> const &vec, size_t index);

  static BigInteger Add(BigInteger const &num1, BigInteger const &num2, int32_t sign);

  static BigInteger Sub(BigInteger num1, BigInteger num2, int32_t sign);

  static std::pair<BigInteger, BigInteger> BigDivMod(BigInteger const &numerator, BigInteger const &denominator);

  static std::pair<BigInteger, BigInteger> DivMod(BigInteger const &numerator, BigInteger const &denominator);

  bool IsLess(BigInteger const &num) const;

 public:
  BigInteger() = default;

  BigInteger(std::string const &st);

  BigInteger(BigInteger const &num);;

  BigInteger(int64_t const &num);

  bool operator==(BigInteger const &num) const;

  bool operator!=(BigInteger const &num) const;

  bool operator<(BigInteger const &num) const;

  bool operator>(BigInteger const &num) const;

  bool operator<=(BigInteger const &num) const;

  bool operator>=(BigInteger const &num) const;

  BigInteger operator+(BigInteger const &num) const;

  BigInteger operator-(BigInteger const &num) const;

  BigInteger operator*(BigInteger const &num);

  BigInteger operator/(BigInteger const & num) const;

  BigInteger operator%(BigInteger const & num) const;

  BigInteger &operator/= (BigInteger const & num);

  BigInteger &operator%= (BigInteger const & num);

  BigInteger &operator*=(BigInteger const &num);

  BigInteger &operator+=(BigInteger const &num);

  BigInteger &operator-=(BigInteger const &num);

  BigInteger operator++(int);

  BigInteger operator--(int);

  BigInteger &operator++();

  BigInteger &operator--();

  void Swap(BigInteger &num);

  operator bool();

  BigInteger &operator=(int32_t num);;

  BigInteger operator-() const;

  [[nodiscard]] int32_t GetSign() const;

  std::string toString() const;

};

std::istream &operator>>(std::istream &in, BigInteger &num);

std::ostream &operator<<(std::ostream &out, BigInteger const &num);

BigInteger Abs(BigInteger const &num);

void swap(BigInteger &num1, BigInteger &num2);

#endif //BIGINTEGER_BIGINTEGER_H
