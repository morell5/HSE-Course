#include "biginteger.h"

std::string setlen(int len, std::string s) {
  std::string out(len - s.size(), '0');
  return out + s;
}

void BigInteger::remove_zeros() {
  while (data.size() > 1 && data.back() == 0) {
    data.pop_back();
  }
  if (data.size() == 1 && data[0] == 0) {
    negative_flag = 0;
  }
}

const BigInteger BigInteger::baseinn(int n) {
  BigInteger copy(*this);
  std::vector<int> tmp(n, 0);
  copy.data.insert(copy.data.begin(), tmp.begin(), tmp.end());
  copy.remove_zeros();
  return copy;
}

std::string BigInteger::toString() {
  std::string out;
  if (negative_flag) {
    out += "-";
  }
  out += std::to_string(data.back());
  for (long long i = data.size() - 2; i >= 0; i--) {
    out += setlen(BigInteger::SIZE, std::to_string(data[i]));
  }
  return out;
}

BigInteger::BigInteger() {
  data = std::vector<int>(1, 0);
  negative_flag = 0;
}

BigInteger::BigInteger(int number) {
  negative_flag = number < 0;
  data.clear();
  number = std::abs(number);
  if (number == 0) {
    data = std::vector<int>(1, 0);
  } else {
    while (number != 0) {
      data.push_back(number % BigInteger::BASE);
      number /= BigInteger::BASE;
    }
  }
  remove_zeros();
}

BigInteger::BigInteger(std::string number) {
  if (number.empty()) {
    negative_flag = 0;
    data = std::vector<int>(1, 0);
  } else {
    if (number[0] == '-') {
      negative_flag = 1;
      number = number.substr(1);
    } else {
      negative_flag = 0;
    }
    for (long long i = number.size(); i > 0; i -= BigInteger::SIZE) {
      if (i >= BigInteger::SIZE) {
        data.push_back(atoi(
            number.substr(i - BigInteger::SIZE, BigInteger::SIZE).c_str()));
      } else {
        data.push_back(atoi(number.substr(0, i).c_str()));
      }
    }
  }
  remove_zeros();
}

BigInteger::BigInteger(std::vector<int> arr) {
  data = arr;
  negative_flag = 0;
  if (data.empty()) {
    data.push_back(0);
  }
  remove_zeros();
}

BigInteger::operator bool() const {
  return !(data.size() == 1 && data[0] == 0);
}

BigInteger& BigInteger::operator=(const BigInteger& other) {
  data = other.data;
  negative_flag = other.negative_flag;
  return *this;
}

BigInteger& BigInteger::operator+=(const BigInteger& other) {
  *this = *this + other;
  return *this;
}

BigInteger& BigInteger::operator-=(const BigInteger& other) {
  *this = *this - other;
  return *this;
}

BigInteger& BigInteger::operator*=(const BigInteger& other) {
  *this = *this * other;
  return *this;
}

BigInteger& BigInteger::operator/=(const BigInteger& other) {
  *this = *this / other;
  return *this;
}

BigInteger& BigInteger::operator%=(const BigInteger& other) {
  *this = *this % other;
  return *this;
}

BigInteger& BigInteger::operator++() {
  *this += 1;
  return *this;
}

const BigInteger BigInteger::operator++(int) {
  BigInteger copy(*this);
  *this += 1;
  return copy;
}

BigInteger& BigInteger::operator--() {
  *this -= 1;
  return *this;
}

const BigInteger BigInteger::operator--(int) {
  BigInteger copy(*this);
  *this += -1;
  return copy;
}

const BigInteger BigInteger::operator-() const {
  BigInteger copy_(*this);
  copy_.negative_flag ^= 1;
  if (copy_.data.size() == 1 && copy_.data[0] == 0) {
    copy_.negative_flag = 0;
  }
  return copy_;
}

std::istream& operator>>(std::istream& in, BigInteger& to_) {
  std::string number;
  in >> number;
  to_ = BigInteger(number);
  return in;
}

std::ostream& operator<<(std::ostream& out, const BigInteger& printing) {
  if (printing.negative_flag) {
    out << "-";
  }
  out << printing.data.back();
  for (long long i = printing.data.size() - 2; i >= 0; i--) {
    out << setlen(BigInteger::SIZE, std::to_string(printing.data[i]));
  }
  return out;
}

bool operator==(const BigInteger& a, const BigInteger& b) {
  return (a.data == b.data && a.negative_flag == b.negative_flag);
}

bool operator!=(const BigInteger& a, const BigInteger& b) { return !(a == b); }

bool operator<(const BigInteger& a, const BigInteger& b) {
  if (a == b) {
    return false;
  }
  if (a.negative_flag && !b.negative_flag) {
    return true;
  }
  if (b.negative_flag && !a.negative_flag) {
    return false;
  }
  if (a.negative_flag && b.negative_flag) {
    if (a.data.size() > b.data.size()) {
      return true;
    }
    if (a.data.size() < b.data.size()) {
      return false;
    }
    for (long long i = a.data.size() - 1; i >= 0; i--) {
      if (a.data[i] != b.data[i]) {
        return a.data[i] > b.data[i];
      }
    }
  }
  if (!a.negative_flag && !b.negative_flag) {
    if (a.data.size() > b.data.size()) {
      return false;
    }
    if (a.data.size() < b.data.size()) {
      return true;
    }
    for (long long i = a.data.size() - 1; i >= 0; i--) {
      if (a.data[i] != b.data[i]) {
        return a.data[i] < b.data[i];
      }
    }
  }
  return 0;
}

bool operator<=(const BigInteger& a, const BigInteger& b) {
  return a < b || a == b;
}

bool operator>(const BigInteger& a, const BigInteger& b) { return !(a < b); }

bool operator>=(const BigInteger& a, const BigInteger& b) { return !(a <= b); }

const BigInteger operator+(BigInteger a, const BigInteger& b) {
  if (a.negative_flag) {
    if (b.negative_flag) {
      return -((-a) + (-b));
    }
    return b - (-a);
  }
  if (b.negative_flag) {
    return b + a;
  }
  int carry = 0;
  for (std::size_t i = 0;
       i < std::max(a.data.size(), b.data.size()) || carry != 0; i++) {
    if (i == a.data.size()) {
      a.data.push_back(0);
    }
    a.data[i] += (i >= b.data.size() ? 0 : b.data[i]) + carry;
    carry = a.data[i] / BigInteger::BASE;
    a.data[i] %= BigInteger::BASE;
  }
  a.remove_zeros();
  return a;
}

const BigInteger operator-(BigInteger a, const BigInteger& b) {
  if (a.negative_flag) {
    if (b.negative_flag) {
      return a + (-b);
    }
    return -((-a) + b);
  }
  if (b.negative_flag) {
    return a + (-b);
  }
  if (a < b) return -(b - a);
  int carry = 0;
  for (std::size_t i = 0;
       i < std::max(a.data.size(), b.data.size()) || carry != 0; i++) {
    if (i == a.data.size()) {
      a.data.push_back(0);
    }
    a.data[i] -= (i >= b.data.size() ? 0 : b.data[i]) + carry;
    carry = 0;
    if (a.data[i] < 0) {
      a.data[i] += BigInteger::BASE;
      carry = 1;
    }
  }
  a.remove_zeros();
  return a;
}

const BigInteger operator*(
    const BigInteger& a,
    const BigInteger& b)  // деление при помощи алгоритма Карацубы
{
  if (a.negative_flag || b.negative_flag) {
    if (a.negative_flag ^ b.negative_flag) {
      return -((a.negative_flag ? -a : a) * (b.negative_flag ? -b : b));
    } else {
      return (-a) * (-b);
    }
  }
  int n = std::max(a.data.size(), b.data.size());
  BigInteger c;
  if (n == 1) {
    c.data[0] = a.data[0] * b.data[0];
    int carry = c.data[0] / BigInteger::BASE;
    c.data[0] %= BigInteger::BASE;
    if (carry) {
      c.data.push_back(carry);
    }
  } else {
    int k = n / 2;
    std::vector<int> a2;
    a2.insert(a2.begin(), a.data.begin(),
              a.data.begin() + std::min(k, (int)a.data.size()));
    std::vector<int> a1;
    if (k <= a.data.size()) {
      a1.insert(a1.begin(), a.data.begin() + k, a.data.end());
    }
    std::vector<int> b2;
    b2.insert(b2.begin(), b.data.begin(),
              b.data.begin() + std::min(k, (int)b.data.size()));
    std::vector<int> b1;
    if (k <= b.data.size()) {
      b1.insert(b1.begin(), b.data.begin() + k, b.data.end());
    }
    BigInteger c1 = BigInteger(a1) * BigInteger(b1);
    BigInteger c2 = BigInteger(a2) * BigInteger(b2);
    BigInteger a12 = BigInteger(a1) + BigInteger(a2);
    BigInteger b12 = BigInteger(b1) + BigInteger(b2);
    BigInteger c3 = a12 * b12;
    BigInteger c312 = c3 - c1 - c2;
    c = c1.baseinn(k + k) + c312.baseinn(k) + c2;
  }
  c.remove_zeros();

  return c;
}

const BigInteger operator/(const BigInteger& a,
                           const BigInteger& b)  // деление столбиком
{
  if (b == BigInteger(0)) {
    throw std::runtime_error("BigInteger: divide by zero!");
  }
  if (a.negative_flag || b.negative_flag) {
    if (a.negative_flag ^ b.negative_flag) {
      return -((a.negative_flag ? -a : a) / (b.negative_flag ? -b : b));
    } else {
      return (-a) / (-b);
    }
  }
  BigInteger ans, cur;
  ans.data = std::vector<int>(a.data.size(), 0);
  for (long long i = ans.data.size() - 1; i >= 0; i--) {
    cur = cur.baseinn(1);
    cur.data[0] = a.data[i];
    cur.remove_zeros();
    int l = 0, r = BigInteger::BASE + 1;
    while (l + 1 != r) {
      int m = (l + r) / 2;
      if (BigInteger(m) * b <= cur) {
        l = m;
      } else {
        r = m;
      }
    }
    ans.data[i] = l;
    cur -= b * BigInteger(l);
  }
  ans.remove_zeros();
  return ans;
}

const BigInteger operator%(const BigInteger& a, const BigInteger& b) {
  if (a.negative_flag) {
    return -((-a) % b);
  }
  return a - b * (a / b);
}