#ifndef BIG_INTEGER_H_
#define BIG_INTEGER_H_

#include <iostream>
#include <string>
#include <vector>

namespace bulumutka {

class BigInteger {
  public:
    BigInteger();
    BigInteger(int value);
    BigInteger(int64_t value);
    BigInteger(const std::string& str);

    BigInteger& operator=(const BigInteger& other);
    BigInteger& operator=(const std::string& str);
    BigInteger& operator=(int value);
    BigInteger& operator=(int64_t value);

    const BigInteger operator+(const BigInteger& other) const;
    const BigInteger operator-(const BigInteger& other) const;
    const BigInteger operator*(const BigInteger& other) const;
    const BigInteger operator/(const BigInteger& other) const;
    const BigInteger operator%(const BigInteger& other) const;
    
    const BigInteger operator+() const;
    const BigInteger operator-() const;

    BigInteger& operator+=(const BigInteger& other);
    BigInteger& operator-=(const BigInteger& other);
    BigInteger& operator*=(const BigInteger& other);
    BigInteger& operator/=(const BigInteger& other);
    BigInteger& operator%=(const BigInteger& other);

    BigInteger& operator++();
    BigInteger operator++(int);
    BigInteger& operator--();
    BigInteger operator--(int);

    bool operator==(const BigInteger& other) const;
    bool operator!=(const BigInteger& other) const;
    bool operator<(const BigInteger& other) const;
    bool operator>(const BigInteger& other) const;
    bool operator<=(const BigInteger& other) const;
    bool operator>=(const BigInteger& other) const;
    operator bool() const;

    friend std::ostream& operator<<(std::ostream& output_stream, const BigInteger& number);
    friend std::istream& operator>>(std::istream& input_stream, BigInteger& number);

    std::string toString() const; 

  private:
    std::vector<int> data_;
    bool negative_;

    static const int kBase;
    static const int kDigitsNumber;
    static const BigInteger kZero;
    static const BigInteger kOne;

    void RemoveLeadingZeros_();
};

namespace internal {

template<class T, class F>
T BinarySearch(const T& start, const T& end, const F func);

template<class T> 
void Reverse(T& collection);

bool IsSign(char ch);

bool IsDigit(char ch);

bool IsCorrectStrNumber(const std::string& number);

void RemoveTrailingZeros(std::string& str);

std::string ProceedInt(int val);

/**
 * Comparator.
 * Returns:
 *      1  - first < second
 *      0  - first == second
 *      -1 - first > second
 */
int Compare(const std::vector<int>& first, const std::vector<int>& second);

void Summation(const std::vector<int>& first, const std::vector<int>& second,
         std::vector<int>& result, const int base);

void Subtraction(const std::vector<int>& first, const std::vector<int>& second,
         std::vector<int>& result, const int base);

void Multiply(const std::vector<int>& first, const std::vector<int>& second,
              std::vector<int>& result, const int base);

void Shift(std::vector<int>& data);

} // namespace internal

} // namespace bulumutka

#endif // BIG_INTEGER_H_
