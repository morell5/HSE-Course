#include <vector>
#include <string>

class BigInteger {
public:

    BigInteger();
    BigInteger(int num);
    BigInteger(const std::string& num);
    BigInteger(const char s, const std::vector<int>& big_num);

    std::string toString() const;

    void clear();

    BigInteger& operator-() const;

    BigInteger& operator=(const BigInteger& big_num);
    BigInteger& operator=(int num);
    BigInteger& operator=(const std::string& num);

    friend bool operator==(const BigInteger& left, const BigInteger& right);
    friend bool operator!=(const BigInteger& left, const BigInteger& right);
    friend bool operator<(const BigInteger& left, const BigInteger& right);
    friend bool operator>(const BigInteger& left, const BigInteger& right);
    friend bool operator<=(const BigInteger& left, const BigInteger& right);
    friend bool operator>=(const BigInteger& left, const BigInteger& right);

    friend BigInteger operator+(const BigInteger& left, const BigInteger& right);
    friend BigInteger operator-(const BigInteger& left, const BigInteger& right);
    friend BigInteger operator*(const BigInteger& left, const BigInteger& right);
    friend BigInteger operator/(const BigInteger& left, const BigInteger& right);
    friend BigInteger operator%(const BigInteger& left, const BigInteger& right);

    BigInteger& operator+=(const BigInteger& right);
    BigInteger& operator-=(const BigInteger& right);
    BigInteger& operator*=(const BigInteger& right);
    BigInteger& operator/=(const BigInteger& right);
    BigInteger& operator%=(const BigInteger& right);

    friend std::istream& operator>>(std::istream& in, BigInteger& big_num);
    friend std::ostream& operator<<(std::ostream& out, const BigInteger& big_num);

    BigInteger operator++(int);
    BigInteger operator--(int);
    BigInteger& operator++();
    BigInteger& operator--();

    static BigInteger abs(const BigInteger& big_num);
    bool is_negative() const;
    bool is_positive() const;
    bool is_neutral() const;

    operator bool() const;

private:

    std::vector<int> big_number;
    char sign;

    void clear_back();
    bool check_string_to_num(const std::string& input);

    static BigInteger division(const BigInteger& left, const BigInteger& right, bool is_div);   

    //Here will be some consts
    static constexpr int MAX_VALUE = 1e8;
    static constexpr int POS_IN_MAX_VALUE = 8;
    static constexpr char POSITIVE = '+';
    static constexpr char NEGATIVE = '-';
    static constexpr char NEUTRAL = '0';
};