#include <vector>
#include <string>
#include <ostream>
#include "biginteger.h"

void my_reverse(std::string& a) {
  int n = a.size();
  for (int i = 0; i < n / 2; ++i) {
    std::swap(a[i], a[n - i - 1]);
  }
}

void BigInteger::_remove_leading_zeros() {
  while (!this->_digits.empty() && this->_digits.back() == 0) {
    this->_digits.pop_back();
  }
  if (this->_digits.empty()) {
    this->_is_negative = false;
  }
}

void BigInteger::_shift_left() {
  if (this->_digits.empty()) {
    this->_digits.push_back(0);
    return;
  }
  this->_digits.push_back(this->_digits[this->_digits.size() - 1]);
  for (size_t i = this->_digits.size() - 2; i > 0; --i) {
    this->_digits[i] = this->_digits[i - 1];
  }
  this->_digits[0] = 0;
}

bool BigInteger::_abs_low(const BigInteger& right) {
  if (this->_digits.size() != right._digits.size()) {
    return this->_digits.size() < right._digits.size();
  }
  for (int i = static_cast<int>(right._digits.size()) - 1; i >= 0; --i) {
    if (this->_digits[i] != right._digits[i]) {
      return this->_digits[i] < right._digits[i];
    }
  }
  return false;
}

void BigInteger::_abs_add(const BigInteger& right) {
  int mx = std::max(right._digits.size(), this->_digits.size());
  this->_digits.resize(mx);
  for (int i = 0; i < right._digits.size(); ++i) {
    this->_digits[i] += right._digits[i];
    if (this->_digits[i] >= BigInteger::MOD) {
      if (i == mx - 1) {
        this->_digits.push_back(0);
      }
      this->_digits[i + 1] += this->_digits[i] / BigInteger::MOD;
      this->_digits[i] %= BigInteger::MOD;
    }
  }
}

void BigInteger::_abs_dif(const BigInteger& right, bool is_lower) {
  int mn = std::min(right._digits.size(), this->_digits.size());
  int mx = std::max(right._digits.size(), this->_digits.size());
  this->_digits.resize(mx);
  for (int i = 0; i < mn; ++i) {
    if (is_lower) {
      this->_digits[i] = right._digits[i] - this->_digits[i];
    } else {
      this->_digits[i] = this->_digits[i] - right._digits[i];
    }
  }
  if (is_lower) {
    for (int i = mn; i < mx; ++i) {
      this->_digits[i] = right._digits[i];
    }
  }
  for (int i = 0; i < mn; ++i) {
    if (this->_digits[i] < 0) {
      if (i + 1 != mx) {
        this->_digits[i] += BigInteger::MOD;
        this->_digits[i + 1]--;
      }
    }
  }
  for (int i = mn; i + 1 < mx && this->_digits[i] < 0; ++i) {
    this->_digits[i] += BigInteger::MOD;
    this->_digits[i + 1]--;
  }
  this->_remove_leading_zeros();
}

std::string BigInteger::_to_str() const {
  int n = this->_digits.size();
  std::string result;
  if (n != 0) {
    for (int i = 0; i + 1 < n; ++i) {
      for (int j = 1; j < BigInteger::MOD; j *= 10) {
        result.push_back('0' + (this->_digits[i] / j % 10));
      }
    }
    for (int i = 1; i < BigInteger::MOD; i *= 10) {
      if (this->_digits[n - 1] / i) {
        result.push_back('0' + (this->_digits[n - 1] / i % 10));
      }
    }
    if (this->_is_negative) {
      result.push_back('-');
    }
    my_reverse(result);
  } else {
    result = "0";
  }
  return result;
}

BigInteger::BigInteger() { this->_is_negative = false; }

BigInteger::BigInteger(int32_t i) {
  this->_is_negative = i < 0;
  if (i != 0) {
    this->_digits.push_back(std::abs(i) % BigInteger::MOD);
    i /= BigInteger::MOD;
    if (i != 0) {
      this->_digits.push_back(std::abs(i));
    }
  }
}

BigInteger::BigInteger(std::string str) {
  if (str.empty()) {
    this->_is_negative = false;
  } else {
    if (str[0] == '-') {
      str = str.substr(1);
      this->_is_negative = true;
    } else {
      this->_is_negative = false;
    }
    for (int i = str.length(); i > 0; i -= 9) {
      if (i < 9) {
        this->_digits.push_back(atoi(str.substr(0, i).c_str()));
      } else {
        this->_digits.push_back(atoi(str.substr(i - 9, 9).c_str()));
      }
    }
    this->_remove_leading_zeros();
  }
}

std::ostream& operator<<(std::ostream& os, const BigInteger& bi) {
  os << bi.toString();
  return os;
}

std::istream& operator>>(std::istream& is, BigInteger& bi) {
  std::string from;
  is >> from;
  bi = BigInteger(from);
  return is;
}

BigInteger::operator bool() const { return !this->_digits.empty(); }

BigInteger BigInteger::operator-() const {
  BigInteger result(*this);
  if (result) {
    result._is_negative = !result._is_negative;
  }
  return result;
}

bool operator<(const BigInteger& left, const BigInteger& right) {
  if (left._is_negative != right._is_negative) {
    return left._is_negative;
  }
  if (left._is_negative) {
    if (left._digits.size() != right._digits.size()) {
      return left._digits.size() > right._digits.size();
    }
    for (int i = left._digits.size() - 1; i >= 0; --i) {
      if (left._digits[i] != right._digits[i]) {
        return left._digits[i] > right._digits[i];
      }
    }
  } else {
    if (left._digits.size() != right._digits.size()) {
      return left._digits.size() < right._digits.size();
    }
    for (int i = left._digits.size() - 1; i >= 0; --i) {
      if (left._digits[i] != right._digits[i]) {
        return left._digits[i] < right._digits[i];
      }
    }
  }
  return false;
}

BigInteger& BigInteger::operator+=(const BigInteger& right) {
  if (this->_is_negative == right._is_negative) {
    this->_abs_add(right);
  } else {
    bool is_lower = this->_abs_low(right);
    if (is_lower) {
      this->_is_negative = !this->_is_negative;
    }
    this->_abs_dif(right, is_lower);
  }
  return (*this);
}

const BigInteger operator*(const BigInteger& left, const BigInteger& right) {
  BigInteger result;
  result._digits.resize(left._digits.size() + right._digits.size() + 1);
  for (int i = 0; i < left._digits.size(); ++i) {
    int carry = 0;
    for (int j = 0; j < right._digits.size() || carry != 0; ++j) {
      long long curr = result._digits[i + j] + carry;
      if (j < right._digits.size()) {
        curr += 1ll * left._digits[i] * right._digits[j];
      }
      result._digits[i + j] = curr % BigInteger::MOD;
      carry = curr / BigInteger::MOD;
    }
  }
  result._is_negative = left._is_negative != right._is_negative;
  result._remove_leading_zeros();
  return result;
}

BigInteger operator/(const BigInteger& left, const BigInteger& right) {
  BigInteger b = right;
  b._is_negative = false;
  BigInteger result, curr;
  result._digits.resize(left._digits.size());
  for (long long i = static_cast<long long>(left._digits.size()) - 1; i >= 0;
       --i) {
    curr._shift_left();
    curr._digits[0] = left._digits[i];
    curr._remove_leading_zeros();
    int x = 0;
    int l = 0;
    int r = BigInteger::MOD;
    while (l <= r) {
      int m = (l + r) / 2;
      BigInteger t = b * BigInteger(m);
      if (t <= curr) {
        x = m;
        l = m + 1;
      } else {
        r = m - 1;
      }
    }
    result._digits[i] = x;
    curr = curr - b * BigInteger(x);
  }
  result._is_negative = left._is_negative != right._is_negative;
  result._remove_leading_zeros();
  return result;
}

BigInteger& BigInteger::operator++() { return (*this) += BigInteger(1); }

BigInteger& BigInteger::operator--() { return (*this) += BigInteger(-1); }

BigInteger& BigInteger::operator-=(const BigInteger& right) {
  return (*this) += (-right);
}

BigInteger operator+(const BigInteger& left, const BigInteger& right) {
  BigInteger result(left);
  result += right;
  return result;
}

BigInteger operator-(const BigInteger& left, const BigInteger& right) {
  BigInteger result(left);
  result -= right;
  return result;
}

BigInteger BigInteger::operator++(int) {
  ++(*this);
  return (*this) + BigInteger(-1);
}

BigInteger BigInteger::operator--(int) {
  --(*this);
  return (*this) + BigInteger(1);
}

bool operator>=(const BigInteger& left, const BigInteger& right) {
  return !(left < right);
}

bool operator>(const BigInteger& left, const BigInteger& right) {
  return right < left;
}

bool operator<=(const BigInteger& left, const BigInteger& right) {
  return !(right < left);
}

bool operator!=(const BigInteger& left, const BigInteger& right) {
  return left < right || right < left;
}

bool operator==(const BigInteger& left, const BigInteger& right) {
  return !(left < right || right < left);
}

BigInteger& BigInteger::operator*=(const BigInteger& right) {
  return (*this) = (*this) * right;
}

BigInteger& BigInteger::operator/=(const BigInteger& right) {
  return (*this) = (*this) / right;
}

const BigInteger operator%(const BigInteger& left, const BigInteger& right) {
  BigInteger result = left - (left / right) * right;
  if (result._is_negative) {
    result += right;
  }
  return result;
}

BigInteger& BigInteger::operator%=(const BigInteger& right) {
  return (*this) = (*this) % right;
}

std::string BigInteger::toString() const { return this->_to_str(); }
