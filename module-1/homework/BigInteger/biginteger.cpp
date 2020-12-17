//
// Created by User on 10.12.2020.
//

#include "biginteger.h"

BigInteger::BigInteger() {
    sign_ = false;
    nums = std::vector<int>();
}

BigInteger::BigInteger(int n) {
    *this = BigInteger((int64_t) n);
}

BigInteger::BigInteger(int64_t n) {
    sign_ = n < 0;
    if (n == 0)
        nums.push_back(0);

    while (n) {
        nums.push_back(n % BASE);
        n /= BASE;
    }
}

BigInteger::BigInteger(const std::string &s) {
    sign_ = s[0] == '-';
    int str_size = s.size();
    for (int i = str_size; i > 0; i -= BASE_LEN) {
        std::string chunk = i < BASE_LEN ? s.substr(0, i) : s.substr(i - BASE_LEN, i);
        nums.emplace_back(std::atoi(chunk.c_str()));
    }
    trim();
}

BigInteger &BigInteger::operator=(const BigInteger &bi) = default;

BigInteger &BigInteger::operator=(int n) {
    *this = BigInteger((int64_t) n);
    return *this;
}


BigInteger &BigInteger::operator=(int64_t n) {
    *this = BigInteger(n);
    return *this;
}

BigInteger &BigInteger::operator=(const std::string &s) {
    *this = BigInteger(s);
    return *this;
}

BigInteger BigInteger::operator+(const BigInteger &s) const {
    BigInteger f = *this;
    f += s;
    return f;
}

BigInteger BigInteger::operator-(const BigInteger &s) const {
    BigInteger f = *this;
    f -= s;
    return f;
}

BigInteger BigInteger::operator*(const BigInteger &s) const {
    BigInteger f = *this;
    f *= s;
    return f;
}

BigInteger BigInteger::operator/(const BigInteger &s) const {
    BigInteger f = *this;
    f /= s;
    return f;
}

BigInteger BigInteger::operator/(int s) const {
    BigInteger f = *this;
    f /= s;
    return f;
}

BigInteger BigInteger::operator%(const BigInteger &s) const {
    BigInteger f = *this;
    f %= s;
    return f;
}

BigInteger BigInteger::operator+=(const BigInteger &s) {
    return plus(s, false);
}

BigInteger BigInteger::operator-=(const BigInteger &s) {
    return plus(s, true);
}

BigInteger BigInteger::operator*=(const BigInteger &s) {
    BigInteger res;
    int ost = 0;

    for (int i = 0; i < nums.size(); i++) {
        for (int j = 0; j < s.nums.size() || ost; j++) {
            int k = i + j;

            if (k >= res.nums.size())
                res.nums.emplace_back(0);
            res.nums[k] += ost + getNum(i) * s.getNum(j);
            ost = 0;

            if (res.nums[k] >= BASE) {
                ost = res.nums[k] / BASE;
                res.nums[k] %= BASE;
            }
        }
    }

    res.sign_ = sign_ ^ s.sign_;

    res.trim();
    *this = res;
    return *this;
}

BigInteger BigInteger::operator/=(const BigInteger &s) {
    if (!s)
        throw std::invalid_argument("Division by zero");

    BigInteger l = 0;
    BigInteger r = abs(*this) + BigInteger(1);

    while (r - l > BigInteger(1)) {
        BigInteger mid = (l + r) / 2;

        if (abs(s) * mid > abs(*this))
            r = mid;
        else
            l = mid;
    }

    l.sign_ = sign_ ^ s.sign_;
    *this = l;
    return *this;
}

BigInteger BigInteger::operator/=(int s) {
    if (s == 0)
        throw std::invalid_argument("Division by zero");

    BigInteger res;
    res.nums.assign(nums.size() + 1, 0);
    std::string div = std::string();

    for (int i = nums.size() - 1; i >= 0; i--) {
        div += std::to_string(nums[i]);
        int tmp = stol(div);

        if (tmp / s > 0) {
            res.nums[i] = tmp / s;
            div = std::to_string(tmp % s);
        }
    }
    res.trim();
    *this = res;
    return *this;
}

BigInteger BigInteger::operator%=(const BigInteger &s) {
    *this -= *this / s * s;
    return *this;
}

BigInteger BigInteger::operator++() {
    *this += 1;
    return *this;
}

BigInteger BigInteger::operator++(int) {
    BigInteger f = *this;
    *this += 1;
    return f;
}

BigInteger BigInteger::operator--() {
    *this -= 1;
    return *this;
}

BigInteger BigInteger::operator--(int) {
    BigInteger f = *this;
    *this -= 1;
    return f;
}

BigInteger BigInteger::operator-() const {
    BigInteger f = *this;
    f.sign_ = !sign_;
    return f;
}

BigInteger BigInteger::operator>(const BigInteger &s) const {
    bool res = false;

    if (sign_ < s.sign_) {
        return true;
    } else if (sign_ > s.sign_) {
        return false;
    }

    for (int i = std::max(s.nums.size(), nums.size()) - 1; i >= 0; i--) {
        if (getNum(i) < s.getNum(i)) {
            res = false;
            break;
        } else if (getNum(i) > s.getNum(i)) {
            res = true;
            break;
        }
    }
    return sign_ == !res;
}

BigInteger BigInteger::operator<(const BigInteger &s) const {
    return (s > *this);
}

BigInteger BigInteger::operator>=(const BigInteger &s) const {
    return !(*this < s);
}

BigInteger BigInteger::operator<=(const BigInteger &s) const {
    bool res = !(*this > s);
    return res;
}

BigInteger BigInteger::operator==(const BigInteger &s) const {
    if (s.sign_ != sign_)
        return false;
    for (int i = 0; i < s.nums.size() || i < nums.size(); i++) {
        if (getNum(i) != s.getNum(i))
            return false;
    }
    return true;
}

BigInteger BigInteger::operator!=(const BigInteger &s) const {
    return !(*this == s);
}

BigInteger::operator bool() const {
    for (auto n : nums) {
        if (n != 0)
            return true;
    }
    return false;
}

std::ostream &operator<<(std::ostream &out, const BigInteger &bi) {
    out << bi.toString();
    return out;
}

std::istream &operator>>(std::istream &in, BigInteger &bi) {
    std::string bi_str;
    in >> bi_str;
    bi = BigInteger(bi_str);
    return in;
}

BigInteger abs(const BigInteger &s) {
    BigInteger copy = s;
    copy.sign_ = s.sign_ != 0;
    return copy;
}

std::string BigInteger::toString() const {
    std::string result = sign_ ? "-" : "";
    int start = nums.size() - 1;
    while (nums[start] == 0)
        start--;
    int first = start;
    for (int i = start; i >= 0; i--) {
        std::string chunk = std::to_string(nums[i]);
        if (i != first) {
            for (int j = 0; j < BASE_LEN - chunk.size(); j++)
                result += "0";
        }
        result += chunk;
    }
    return result;
}

void BigInteger::trim() {
    while (nums.size() > 1 && nums.back() == 0)
        nums.pop_back();
}

int BigInteger::getNum(int idx) const {
    return idx < nums.size() ? nums[idx] : 0;
}

BigInteger &BigInteger::plus(const BigInteger &s, bool isSubtract) {
    int ost = 0;
    bool thisBigger = abs(s) < abs(*this);
    bool sub = sign_ ^s.sign_ ^isSubtract;

    for (int i = 0; i < nums.size() || i < s.nums.size() || ost != 0; i++) {
        if (i >= nums.size())
            nums.emplace_back(0);
        if (sub) {
            if (thisBigger)
                nums[i] -= s.getNum(i);
            else
                nums[i] = s.getNum(i) - getNum(i);
        } else
            nums[i] += s.getNum(i);

        nums[i] += ost;
        ost = 0;
        if (nums[i] >= BASE) {
            nums[i] -= BASE;
            ost++;
        } else if (nums[i] < 0) {
            nums[i] += BASE;
            ost--;
        }
    }

    if (!thisBigger)
        sign_ = s.sign_ ^ isSubtract;

    trim();
    return *this;
}
