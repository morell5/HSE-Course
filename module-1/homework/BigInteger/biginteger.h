#include <vector>
#include <iostream>
#include <string>


class BigInteger {
    std::vector<int> _data;
    int sign{};
    static int const base = 1e9;

    int _at(int i) const {
        return i < _data.size() ? _data[i] : 0;
    }

    static BigInteger sub(BigInteger const &_this, BigInteger const &number,
                          int sign);

    static std::pair<BigInteger, int> div(BigInteger const &_this, int number);


public:
    BigInteger() = default;

    BigInteger(int number);

    BigInteger(std::string const &number);

    BigInteger(BigInteger const &number);

    BigInteger &operator=(int number);

    BigInteger operator-();

    BigInteger operator+(BigInteger const &number) const;

    BigInteger &operator+=(BigInteger const &number);

    BigInteger &operator-=(BigInteger const &number);

    BigInteger operator-(BigInteger const &number) const;

    BigInteger operator*(int number) const;

    BigInteger operator*(BigInteger const &number) const;

    BigInteger &operator*=(BigInteger const &number);

    BigInteger operator%(int number) const;

    BigInteger &operator%=(int number);

    BigInteger operator/(int number) const;

    BigInteger &operator/=(int number);

    BigInteger &operator++();

    BigInteger operator++(int);

    BigInteger &operator--();

    BigInteger operator--(int);

    bool operator>(BigInteger const &number) const;

    bool operator>=(BigInteger const &number) const;

    bool operator==(BigInteger const &number) const;

    bool operator!=(BigInteger const &number) const;


    bool operator<(BigInteger const &number) const;

    bool operator<=(BigInteger const &number) const;

    std::string toString() const;

    operator bool() const;

};

std::ostream &operator<<(std::ostream &out, BigInteger const &number);

std::istream &operator>>(std::istream &in, BigInteger &number);