
#include <vector>
#include <iostream>
#include <string>

class BigInteger {
private:

    friend BigInteger multiplication(BigInteger& left_value, BigInteger& right_value);
    friend BigInteger addition(BigInteger& left_value, BigInteger& right_value);
    friend BigInteger division(BigInteger& left_value, BigInteger& right_value);
    friend BigInteger subtraction(BigInteger& left_value, BigInteger& right_value);

    friend int get_digit(BigInteger& num, int index);
    friend void recalc(BigInteger& num, int index);

    friend void prepare_for_mp(BigInteger& value, int size);
    friend std::pair<BigInteger, BigInteger> cut_value_for_mp(BigInteger& value);
    friend void cleaning_value_from_zero(BigInteger& value);
    friend void adding_zero_to_the_begining(BigInteger& value, int kol);

public:

    friend std::istream& operator >> (std::istream& in, BigInteger& value);
    friend std::ostream& operator << (std::ostream& out, const BigInteger& value);

private:

    std::vector<char> original_number;

    int size() const;

    bool sign() const;

    void push_back(int value);
    void push_back(char value);

    void pop_back();
    void pop_front();

    void push_front(int value);
    void push_front(char value);

    char& operator [] (int index);

    std::vector<char> make_number(int value);
    std::vector<char> make_number(std::string& value);

public:

    BigInteger();
    BigInteger(int value);
    BigInteger(const BigInteger& value);

    ~BigInteger();

    BigInteger& operator = (int value);

    bool operator == (BigInteger& value);
    bool operator != (BigInteger& value);

    bool operator > (BigInteger& value);
    bool operator >= (BigInteger& value);
    bool operator < (BigInteger& value);
    bool operator <= (BigInteger& value);

    BigInteger operator + (const BigInteger& value);
    BigInteger operator - (const BigInteger& value);
    BigInteger operator * (const BigInteger& value);
    BigInteger operator / (const BigInteger& value);
    BigInteger operator % (const BigInteger& value);

    BigInteger& operator += (const BigInteger& value);
    BigInteger& operator -= (const BigInteger& value);
    BigInteger& operator *= (const BigInteger& value);
    BigInteger& operator /= (const BigInteger& value);
    BigInteger& operator %= (const BigInteger& value);

    BigInteger& operator --();
    BigInteger& operator ++();

    BigInteger operator --(int);
    BigInteger operator ++(int);

    BigInteger operator -();

    operator bool() const;

    std::string toString();

};
