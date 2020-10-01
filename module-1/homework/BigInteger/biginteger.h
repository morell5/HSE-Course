#include <iostream>
#include <string>
#include <vector>

class BigInteger {
 public:
  static const int BASE = 1e4;
  static const int SIZE = 4;
  BigInteger();
  BigInteger(int number);
  BigInteger(std::string number);
  operator bool() const;
  std::string toString();
  BigInteger& operator=(const BigInteger& other);
  BigInteger& operator+=(const BigInteger& other);
  BigInteger& operator-=(const BigInteger& other);
  BigInteger& operator*=(const BigInteger& other);
  BigInteger& operator/=(const BigInteger& other);
  BigInteger& operator%=(const BigInteger& other);
  const BigInteger operator-() const;
  BigInteger& operator++();
  const BigInteger operator++(int);
  BigInteger& operator--();
  const BigInteger operator--(int);

  friend std::istream& operator>>(std::istream& in, BigInteger& to_);
  friend std::ostream& operator<<(std::ostream& out,
                                  const BigInteger& printing);
  friend bool operator==(const BigInteger& a, const BigInteger& b);
  friend bool operator!=(const BigInteger& a, const BigInteger& b);
  friend bool operator<(const BigInteger& a, const BigInteger& b);
  friend bool operator<=(const BigInteger& a, const BigInteger& b);
  friend bool operator>(const BigInteger& a, const BigInteger& b);
  friend bool operator>=(const BigInteger& a, const BigInteger& b);
  friend const BigInteger operator+(BigInteger a, const BigInteger& b);
  friend const BigInteger operator-(BigInteger a, const BigInteger& b);
  friend const BigInteger operator*(const BigInteger& a, const BigInteger& b);
  friend const BigInteger operator/(const BigInteger& a, const BigInteger& b);
  friend const BigInteger operator%(const BigInteger& a, const BigInteger& b);

 private:
  BigInteger(std::vector<int> arr);  // конструктор положительного числа из
                                     // массива data - служебный
  std::vector<int> data;  // само число будем хранить в векторе
  bool negative_flag;  // флаг отрицательности числа
  void remove_zeros();  // служебная функция - удаляет ведущие нули.
  const BigInteger baseinn(
      int n);  //служебная функция - возвращает число, умноженное на BASE^n
};