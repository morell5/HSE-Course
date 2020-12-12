#ifndef BIGINTEGER_BIGINTEGER_H
#define BIGINTEGER_BIGINTEGER_H

#include <string>
#include <vector>

static const int MOD = 1000000000;

class BigInteger {
private:
    int digits_number;
    std::vector<int> digits;
    bool sign;
public:
    BigInteger();
    BigInteger(int n);

    explicit operator int () const;
    explicit operator bool() const;

    BigInteger &operator=(const BigInteger &b);
    BigInteger &operator=(const int        &x);

    bool operator==(const BigInteger& b);
    bool operator!=(const BigInteger& b);
    bool operator< (const BigInteger& b);
    bool operator> (const BigInteger& b);
    bool operator<=(const BigInteger& b);
    bool operator>=(const BigInteger& b);

    BigInteger operator+(      BigInteger  b);
    BigInteger operator-(      BigInteger  b);
    BigInteger operator*(const BigInteger& b);
    BigInteger operator/(const BigInteger& b);
    BigInteger operator%(      BigInteger  b);

    BigInteger& operator+=(const BigInteger& b);
    BigInteger& operator-=(const BigInteger& b);
    BigInteger& operator*=(const BigInteger& b);
    BigInteger& operator/=(const BigInteger& b);
    BigInteger& operator%=(const BigInteger& b);

    BigInteger& operator++(   );
    BigInteger  operator++(int);
    BigInteger& operator--(   );
    BigInteger  operator--(int);

    friend std::ostream& operator<<(std::ostream& out, const BigInteger &b);
    friend std::istream& operator>>(std::istream& in ,       BigInteger &b);

    BigInteger operator-();
    std::string toString() const;

    BigInteger half();
    static BigInteger ten_pow(int n);
};

#endif //BIGINTEGER_BIGINTEGER_H