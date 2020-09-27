#include <iostream>
#include <vector>
#include <string>

class BigInteger {

    const static int BASE = 10;

public:
    // C++ standard behaviour for uninitialized variables is undefined value, so not assigning a value here
    BigInteger() {
        _digits = new std::vector<int>();
    }

    BigInteger(int num): BigInteger() {
        // special case: 0
        if (num == 0) {
            _digits->push_back(0);
            return;
        }

        // sign
        _digits->push_back(num < 0);
        if (num < 0) {
            num = -num;
        }

        while (num) {
            _digits->push_back(num % BASE);
            num /= BASE;
        }
    }

    BigInteger(const BigInteger& other): BigInteger() {
        if (other._digits) {
            for (int el: *other._digits) {
                _digits->push_back(el);
            }
        }
    }

    ~BigInteger() {
        delete _digits;
    }

    explicit operator int() const;

    explicit operator bool() const;

    BigInteger& operator=(const BigInteger& other);

    BigInteger operator-();

    // --------- comparison operators ------------

    bool operator<(const BigInteger& other) const;

    bool operator>(const BigInteger& other) const;

    bool operator==(const BigInteger& other) const;

    bool operator>=(const BigInteger& other) const;

    bool operator<=(const BigInteger& other) const;

    bool operator !=(const BigInteger& other) const;

    //------------ arithmetic operators ---------------

    friend BigInteger operator+(const BigInteger& lhs, const BigInteger& rhs);

    friend BigInteger operator-(const BigInteger& lhs, const BigInteger& rhs);

    friend BigInteger operator*(const BigInteger& lhs, const BigInteger& rhs);

    friend BigInteger operator/(const BigInteger& lhs, const BigInteger& rhs);

    friend BigInteger operator%(const BigInteger& lhs, const BigInteger& rhs);

    // ------------ compound assignment operators ----------------

    BigInteger& operator+=(const BigInteger& other);

    BigInteger& operator-=(const BigInteger& other);

    BigInteger& operator*=(const BigInteger& other);

    BigInteger& operator/=(const BigInteger& other);

    BigInteger& operator%=(const BigInteger& other);

    // ----------- increment/decrement --------------

    BigInteger& operator++();

    BigInteger operator++(int);

    BigInteger& operator--();

    BigInteger operator--(int);

    // ------------- I/O ---------------

    friend std::ostream& operator<<(std::ostream& output, const BigInteger& num);

    friend std::istream& operator>>(std::istream& input, BigInteger& num);

    std::string toString();

private:
    // storing the digits in reversed order for conveniency
    // first element is the sign (0 for +, 1 for -)
    // if the number is 0, the vector consists of one element = 0
    std::vector<int>* _digits = nullptr;

    // returns -1 if this is smaller than other
    // 0 if equal
    // 1 if this is greater
    int compareModulus(const BigInteger& other) const;

    bool isPositive() const;

    static BigInteger sum(const BigInteger& lhs, const BigInteger& rhs, bool sign);

    static BigInteger substract(const BigInteger& lhs, const BigInteger& rhs, bool sign);
};