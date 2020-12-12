//
// Created by Евгений on 17.11.2020.
//

#include <iostream>
#include "biginteger.h"

BigInteger::BigInteger() {
    sign = false;
    digits_number = 1;;
    digits = std::vector<int>(digits_number);
}

BigInteger::BigInteger(int n) {
    sign = n < 0;
    digits_number = 1;
    digits = std::vector<int>(digits_number);
    digits[0] = sign ? -n : n;
}

bool BigInteger::operator==(const BigInteger& b) {
    if (sign != b.sign || digits_number != b.digits_number)
        return false;

    for (int i = 0; i < digits_number; ++i)
        if (digits[i] != b.digits[i])
            return false;

    return true;
}

bool BigInteger::operator!=(const BigInteger& b) {
    return !(*this == b);
}

bool BigInteger::operator<(const BigInteger& b) {
    if (sign != b.sign)
        return sign;

    bool abs_less;
    if (digits_number == b.digits_number){

        int i = digits_number - 1;
        while (i > -1 && digits[i] == b.digits[i])
            --i;

        if (i == -1)
            return false;

        abs_less = digits[i] < b.digits[i];
    }
    else
        abs_less = digits_number < b.digits_number;

    return sign ? !abs_less : abs_less;
}

bool BigInteger::operator>(const BigInteger& b) {
    if (sign != b.sign)
        return !sign;

    bool abs_higher;
    if (digits_number == b.digits_number){

        int i = digits_number - 1;
        while (i > -1 && digits[i] == b.digits[i])
            --i;

        if (i == -1)
            return false;

        abs_higher = digits[i] > b.digits[i];
    }
    else
        abs_higher = digits_number > b.digits_number;

    return sign ? !abs_higher : abs_higher;
}

bool BigInteger::operator<=(const BigInteger& b) {
    return !operator>(b);
}

bool BigInteger::operator>=(const BigInteger& b) {
    return !operator<(b);
}

std::string BigInteger::toString() const {
    std::string ans = sign ? "-" : "";
    std::string digit;
    for (int i = digits_number - 1; i > -1; --i){
        digit = std::to_string(digits[i]);

        if (i != digits_number - 1)
            for (int c = 0; c < 9 - digit.length(); ++c)
                ans += '0';

        ans += digit;
    }

    return ans;
}

BigInteger BigInteger::operator+(BigInteger b) {
    BigInteger ans = BigInteger();
    ans.digits.clear();

    if (sign == b.sign){
        int delta = 0; // Перенос разряда
        int new_digit; // Число в текущем разряде
        int max_digits = digits_number > b.digits_number ?
                digits_number : b.digits_number; // Максимальное число разрядов

        for (int i = 0; i < max_digits; ++i){
            if (i >= digits_number){
                new_digit = (b.digits[i] + delta) % MOD;
                delta = new_digit == 0 ? 1 : 0;
                ans.digits.push_back(new_digit);
                continue;
            }
            if (i >= b.digits_number){
                new_digit = (digits[i] + delta) % MOD;
                delta = new_digit == 0 ? 1 : 0;
                ans.digits.push_back(new_digit);
                continue;
            }
            new_digit = digits[i] + delta + b.digits[i];
            delta = new_digit / MOD;
            new_digit %= MOD;
            ans.digits.push_back(new_digit);
        }

        if (delta) {
            ans.digits.push_back(delta);
            ans.digits_number = max_digits + 1;
        } else
            ans.digits_number = max_digits;

        ans.sign = sign;
        return ans;
    }

    return operator-(-b);
}

BigInteger BigInteger::operator-(BigInteger b) {
    BigInteger ans = BigInteger();
    ans.digits.clear();

    if (sign == b.sign){

        if (*this == b)
            return BigInteger();

        // Вычитаем всегда из числа с большим модулем
        if (!sign && *this < b || sign && *this > b)
            return -(b - *this);

        int delta = 0; // Заимствование разряда
        int new_digit; // Число в текущем разряде
        int second_number_digit; // Число в текущем разряде второго числа

        for (int i = 0; i < digits_number; ++i){
            second_number_digit = i < b.digits_number ? b.digits[i] : 0;
            new_digit = digits[i] + delta - second_number_digit;

            delta = new_digit < 0 ? -1 : 0;
            new_digit += new_digit < 0 ? MOD : 0;
            ans.digits.push_back(new_digit);
        }

        ans.digits_number = digits_number;
        while (!ans.digits.empty() && !ans.digits.back()){
            ans.digits.pop_back();
            --ans.digits_number;
        }

        ans.sign = sign;
        return ans;
    }

    return operator+(-b);
}

BigInteger BigInteger::operator*(const BigInteger& b) {
    BigInteger ans = BigInteger();
    ans.digits.clear();
    ans.digits_number = 0;

    int delta; // Заимствование разряда
    long long new_digit; // Число в текущем разряде
    for (int last_digit = 0; last_digit < b.digits_number; ++last_digit){
        if (b.digits[last_digit] == 0){
            if (ans.digits_number == last_digit){
                ans.digits.push_back(0);
                ++ans.digits_number;
            }
            continue;
        }

        delta = 0;
        for (int digit = 0; digit < digits_number; ++digit){
            new_digit = (long long)b.digits[last_digit] * digits[digit] + delta;

            if (last_digit + digit < ans.digits_number)
                new_digit += ans.digits[last_digit + digit];

            delta = new_digit / MOD;
            new_digit %= MOD;

            if (last_digit + digit < ans.digits_number)
                ans.digits[last_digit + digit] = new_digit;
            else{
                ans.digits.push_back(new_digit);
                ++ans.digits_number;
            }
        }
        if (delta){
            if (last_digit + digits_number == ans.digits_number){
                ans.digits_number++;
                ans.digits.push_back(delta);
            }
            else
                ans.digits.back() += delta;
        }
    }

    ans.sign = sign != b.sign;
    return ans;
}

BigInteger BigInteger::ten_pow(int n) {
    int billions = n / 9;
    int ost = n % 9;
    int tens = 1;

    for (int i = 0; i < ost; ++i)
        tens *= 10;
    BigInteger ans = tens;
    for (int i = 0; i < billions; ++i)
        ans *= 1000000000;
    return ans;
}

BigInteger BigInteger::operator/(const BigInteger& b) {
    bool a_sign = sign;
    sign = false;

    BigInteger new_b = b;
    new_b.sign = false;

    if (operator<(new_b)){
        sign = a_sign;
        return BigInteger();
    }

    int diff = toString().length() - new_b.toString().length();
    BigInteger l = diff == 0 ? 1 : ten_pow(diff - 1);
    BigInteger r = diff == 0 ? l * 10 : l * 100;

    while (r - l != 1){
        BigInteger m = (l + r).half();
        if (operator<(new_b * m))
            r = m;
        else
            l = m;
    }

    sign = a_sign;
    l.sign = sign != b.sign;
    l.digits_number = l.digits.size();
    return l;
}

BigInteger BigInteger::operator%(BigInteger b) {
    return operator-(b * operator/(b));
}

BigInteger BigInteger::operator-() {
    BigInteger ans = *this;
    ans.sign = !ans.sign;
    return ans;
}

BigInteger &BigInteger::operator=(const BigInteger& b) {
    if (this == &b)
        return *this;

    sign = b.sign;
    digits_number = b.digits_number;
    digits.clear();
    for (auto digit : b.digits)
        digits.push_back(digit);

    return *this;
}

BigInteger &BigInteger::operator=(const int &x) {
    *this = BigInteger(x);
    return *this;
}

std::ostream &operator<<(std::ostream &out, const BigInteger &b) {
    out << b.toString();
    return out;
}

std::istream &operator>>(std::istream &in, BigInteger &b) {
    std::string s;
    char c = in.peek();
    while (c == ' '){
        in >> c;
        c = in.peek();
    }

    b = BigInteger();
    if (c != '-' && (c < '0' || c > '9'))
        return in;

    if (c == '-'){
        in >> c;
        c = in.peek();
        b.sign = true;
    }

    b.digits.clear();
    b.digits_number = 0;
    while (c >= '0' && c <= '9'){
        in >> c;
        s += c;
        c = in.peek();
    }

    int n = s.length();
    int digits = (n + 8) / 9;
    for (int i = 1; i < digits; ++i){
        b.digits.push_back(
                std::atoi(
                s.substr(n - 9 * i, 9).c_str()
                ));
        ++b.digits_number;
    }
    b.digits.push_back(
            std::atoi(
                    s.substr(0, n - (digits - 1) * 9).c_str()
            ));
    ++b.digits_number;

    return in;
}

BigInteger::operator int() const {
    if (digits_number == 1)
        return digits[0];

    return digits[0] + digits[1] * MOD;
}

BigInteger::operator bool() const {
    return !(digits_number == 1 && digits[0] == 0);
}

BigInteger &BigInteger::operator+=(const BigInteger& b) {
    *this = *this + b;
    return *this;
}

BigInteger &BigInteger::operator-=(const BigInteger& b) {
    *this = *this - b;
    return *this;
}

BigInteger &BigInteger::operator*=(const BigInteger& b) {
    *this = *this * b;
    return *this;
}

BigInteger &BigInteger::operator/=(const BigInteger& b) {
    *this = *this / b;
    return *this;
}

BigInteger &BigInteger::operator%=(const BigInteger& b) {
    *this = *this % b;
    return *this;
}

BigInteger& BigInteger::operator++() {
    *this += 1;
    return *this;
}

BigInteger BigInteger::operator++(int) {
    BigInteger last = *this;
    *this += 1;
    return last;
}

BigInteger& BigInteger::operator--() {
    *this -= 1;
    return *this;
}

BigInteger BigInteger::operator--(int) {
    BigInteger last = *this;
    *this -= 1;
    return last;
}

BigInteger BigInteger::half() {
    BigInteger ans = BigInteger();
    ans.digits.clear();

    std::vector<int> ans_digits;
    int delta = 0; // Перенос разряда

    for (int i = digits_number - 1; i > -1; --i){
        ans_digits.push_back((MOD * delta + digits[i]) / 2);
        delta = digits[i] % 2;
    }

    for (auto i = ans_digits.rbegin(); i != ans_digits.rend(); ++i)
        ans.digits.push_back(*i);

    if (!ans.digits.back()){
        ans.digits.pop_back();
        ans.digits_number = digits_number - 1;
    } else
        ans.digits_number = digits_number;

    ans.sign = sign;
    return ans;
}

