#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class BigInteger {
 public:
  static const int BASE = 100;
  static const int LG = 2;
  bool sign{false};
 
  std::vector<int> poly;
  class ArithmeticsException : public std::exception {};

  BigInteger();
  BigInteger(std::string);

  BigInteger(const char*);
  BigInteger(signed int);
  BigInteger(unsigned int);
  BigInteger(int64_t);

  /**
   * IO operators
   */
  friend std::istream& operator>>(std::istream&, BigInteger&);
  friend std::ostream& operator<<(std::ostream&, const BigInteger&);

  // Unary
  const BigInteger operator-() const;

  /**
   * Postfix
   */
  // Plus plus
  BigInteger& operator++();
  BigInteger operator++(int);
  // Minus minus
  BigInteger& operator--();
  BigInteger operator--(int);

  /**
   * Arithmetics
   */
  const BigInteger operator+(const BigInteger&) const;
  BigInteger& operator+=(const BigInteger&);
  const BigInteger operator-(const BigInteger&) const;
  BigInteger& operator-=(const BigInteger&);
  const BigInteger operator*(const BigInteger&) const;
  BigInteger& operator*=(const BigInteger&);
  const BigInteger operator/(const BigInteger&) const;
  BigInteger& operator/=(const BigInteger&);
  const BigInteger operator%(const BigInteger&) const;
  BigInteger& operator%=(const BigInteger&);

  /**
   * Comparison
   */
  friend bool operator==(const BigInteger&, const BigInteger&);
  friend bool operator<(const BigInteger&, const BigInteger&);
  friend bool operator!=(const BigInteger&, const BigInteger&);
  friend bool operator<=(const BigInteger&, const BigInteger&);
  friend bool operator>(const BigInteger&, const BigInteger&);
  friend bool operator>=(const BigInteger&, const BigInteger&);

  /**
   * Cast
   */
  operator bool() const;
  operator std::string() const;

  std::string toString() const { return std::string(*this); }

  /**
   * Utils
   */
  void trim();
  void shright();
};