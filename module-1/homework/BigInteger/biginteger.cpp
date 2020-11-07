#include "biginteger.h"

/**
 * Utils
 */
const BigInteger BigInteger::slowMultiply(const BigInteger& lhs,
                                          const BigInteger& rhs) {
  BigInteger result;
  result.poly.resize(lhs.poly.size() + rhs.poly.size());
  for (size_t i = 0; i < lhs.poly.size(); i++) {
    int carry = 0;

    for (size_t j = 0; j < rhs.poly.size() || carry != 0; j++) {
      size_t cur = result.poly[i + j] + carry;
      if (j < rhs.poly.size()) {
        cur += 1LL * lhs.poly[i] * rhs.poly[j];
      }

      result.poly[i + j] = static_cast<int>(cur % BigInteger::BASE);
      carry = static_cast<int>(cur / BigInteger::BASE);
    }
  }

  result.sign = lhs.sign != rhs.sign;
  result.trim();

  return result;
}

const BigInteger BigInteger::shortPower(const BigInteger& a, int n) {
  BigInteger res(1);
  BigInteger cpa = a;
  while (n) {
    if (n & 1) {
      res = BigInteger::slowMultiply(res, cpa);
    }

    cpa = BigInteger::slowMultiply(cpa, cpa);
    n >>= 1;
  }
  return res;
}

void BigInteger::trim() {
  while (poly.size() > 1 && poly.back() == 0) {
    poly.pop_back();
  }

  if (poly.size() == 1 && *poly.begin() == 0)
    sign = false;
}

void BigInteger::shright() {
  if (poly.empty()) {
    poly.push_back(0);
    return;
  }

  poly.push_back(poly[poly.size() - 1]);
  for (int64_t i = int64_t(poly.size()) - 2; i > 0; i--)
    poly[i] = poly[i - 1];

  poly[0] = 0;
}

/**
 * BigInteger implementation
 */

BigInteger::BigInteger() {
  sign = false;
}

BigInteger::BigInteger(std::string str) {
  if (str.length() == 0) {
    sign = false;
  } else {
    if (str[0] == '-') {
      str = str.substr(1);
      sign = true;
    } else {
      sign = false;
    }

    for (int i = str.length(); i > 0; i -= BigInteger::LG) {
      if (i < BigInteger::LG)
        poly.push_back(std::atoi(str.substr(0, i).c_str()));
      else
        poly.push_back(
            std::atoi(str.substr(i - BigInteger::LG, BigInteger::LG).c_str()));
    }

    trim();
  }
}

BigInteger::BigInteger(const char* cstr) {
  std::string str = std::string(cstr);
  if (str.length() == 0) {
    sign = false;
  } else {
    if (str[0] == '-') {
      str = str.substr(1);
      sign = true;
    } else {
      sign = false;
    }

    for (int i = str.length(); i > 0; i -= BigInteger::LG) {
      if (i < BigInteger::LG)
        poly.push_back(std::atoi(str.substr(0, i).c_str()));
      else
        poly.push_back(
            std::atoi(str.substr(i - BigInteger::LG, BigInteger::LG).c_str()));
    }

    trim();
  }
}

BigInteger::BigInteger(signed int i) {
  sign = (i < 0);

  poly.push_back(std::abs(i) % BigInteger::BASE);
  i /= BigInteger::BASE;

  if (i != 0)
    poly.push_back(std::abs(i));
}

BigInteger::BigInteger(int64_t i) {
  sign = (i < 0);

  poly.push_back(std::abs(i) % BigInteger::BASE);
  i /= BigInteger::BASE;

  if (i != 0)
    poly.push_back(std::abs(i));
}

BigInteger::BigInteger(unsigned int i) {
  poly.push_back(i % BigInteger::BASE);
  i /= BigInteger::BASE;

  if (i != 0)
    poly.push_back(i);
}

std::ostream& operator<<(std::ostream& os, const BigInteger& bi) {
  if (bi.poly.empty()) {
    os << 0;
  } else {
    if (bi.sign)
      os << '-';

    os << bi.poly.back();
    char old_fill = os.fill('0');
    for (int i = bi.poly.size() - 2; i >= 0; i--)
      os << std::setw(BigInteger::LG) << bi.poly[i];

    os.fill(old_fill);
  }

  return os;
}

std::istream& operator>>(std::istream& is, BigInteger& bi) {
  std::string input;
  is >> input;
  bi = BigInteger(input);
  return is;
}

/**
 * Compare operators
 */

bool operator==(const BigInteger& lhs, const BigInteger& rhs) {
  if (lhs.sign != rhs.sign)
    return false;
  if (lhs.poly.empty()) {
    return rhs.poly.empty() || (rhs.poly.size() == 1 && rhs.poly[0] == 0);
  }

  if (rhs.poly.empty()) {
    return lhs.poly.size() == 1 && lhs.poly[0] == 0;
  }

  if (lhs.poly.size() != rhs.poly.size())
    return false;

  for (size_t i = 0; i < lhs.poly.size(); i++)
    if (lhs.poly[i] != rhs.poly[i])
      return false;

  return true;
}

bool operator<(const BigInteger& lhs, const BigInteger& rhs) {
  if (lhs == rhs)
    return false;

  if (lhs.sign) {
    if (!rhs.sign)
      return true;
    return ((-rhs) < (-lhs));
  } else if (rhs.sign)
    return false;
  else {
    if (lhs.poly.size() != rhs.poly.size()) {
      return lhs.poly.size() < rhs.poly.size();
    } else {
      for (int64_t i = lhs.poly.size() - 1; i >= 0; i--) {
        if (lhs.poly[i] != rhs.poly[i])
          return lhs.poly[i] < rhs.poly[i];
      }

      return false;
    }
  }
}

bool operator!=(const BigInteger& lhs, const BigInteger& rhs) {
  return !(lhs == rhs);
}

bool operator<=(const BigInteger& lhs, const BigInteger& rhs) {
  return (lhs < rhs || lhs == rhs);
}

bool operator>(const BigInteger& lhs, const BigInteger& rhs) {
  return !(lhs <= rhs);
}

bool operator>=(const BigInteger& lhs, const BigInteger& rhs) {
  return !(lhs < rhs);
}

/**
 * Unary operators
 */
const BigInteger BigInteger::operator-() const {
  BigInteger copy(*this);
  copy.sign = !copy.sign;
  return copy;
}

BigInteger& BigInteger::operator++() {
  return *this = (*this += 1);
}

BigInteger BigInteger::operator++(int) {
  *this += BigInteger(1);
  return (*this - BigInteger(1));
}

BigInteger& BigInteger::operator--() {
  return *this -= BigInteger(1);
}

BigInteger BigInteger::operator--(int) {
  *this -= BigInteger(1);
  return *this + BigInteger(1);
}

/**
 * Binary operators
 */
BigInteger& BigInteger::operator+=(const BigInteger& rhs) {
  if (sign) {
    if (rhs.sign)
      return *this = -(-(*this) + (-rhs));
    else
      return *this = rhs - (-(*this));
  } else if (rhs.sign)
    return *this = *this - (-rhs);

  int carry = 0;
  for (size_t i = 0; i < std::max(poly.size(), rhs.poly.size()) || carry != 0;
       ++i) {
    if (i == poly.size())
      poly.push_back(0);
    poly[i] += carry + (i < rhs.poly.size() ? rhs.poly[i] : 0);
    carry = poly[i] >= BigInteger::BASE;
    if (carry != 0)
      poly[i] -= BigInteger::BASE;
  }

  return *this;
}

const BigInteger BigInteger::operator+(const BigInteger& rhs) const {
  BigInteger result = *this;
  result += rhs;
  return result;
}

BigInteger& BigInteger::operator-=(const BigInteger& rhs) {
  if (rhs.sign)
    return *this = *this + (-rhs);
  else if (sign)
    return *this = -(-*this + rhs);
  else if (*this < rhs) {
    return *this = -(rhs - *this);
  }

  int carry = 0;
  for (size_t i = 0; i < rhs.poly.size() || carry != 0; ++i) {
    poly[i] -= carry + (i < rhs.poly.size() ? rhs.poly[i] : 0);
    carry = poly[i] < 0;
    if (carry != 0)
      poly[i] += BigInteger::BASE;
  }

  trim();
  return *this;
}

const BigInteger BigInteger::operator-(const BigInteger& rhs) const {
  BigInteger result = *this;
  result -= rhs;
  return result;
}

BigInteger& BigInteger::operator*=(const BigInteger& rhs) {
  if (poly.size() < 2) {
    return *this = BigInteger::slowMultiply(rhs, *this);
  } else if (rhs.poly.size() < 2) {
    return *this = BigInteger::slowMultiply(*this, rhs);
  }

  const int half_size =
      std::min(std::min(poly.size(), rhs.poly.size()),
               std::max(poly.size() / 2, rhs.poly.size() / 2));

  BigInteger a{0};
  BigInteger b{0};
  BigInteger c{0};
  BigInteger d{0};

  a.poly = std::vector<int>(poly.begin() + half_size, poly.end());
  b.poly = std::vector<int>(poly.begin(), poly.begin() + half_size);

  c.poly = std::vector<int>(rhs.poly.begin() + half_size, rhs.poly.end());
  d.poly = std::vector<int>(rhs.poly.begin(), rhs.poly.begin() + half_size);

  BigInteger base = BigInteger(BigInteger::BASE),
             square = shortPower(base, (half_size * 2)),
             half_square = shortPower(base, (half_size));

  BigInteger ac = a * c;
  BigInteger bd = b * d;

  BigInteger ad_bc = BigInteger::slowMultiply((a + b), (c + d));
  ad_bc -= ac;
  ad_bc -= bd;

  *this = BigInteger::slowMultiply(ac, square) + BigInteger::slowMultiply(ad_bc, half_square) + bd;
  if (sign ^ rhs.sign) {
    sign = true;
  }

  return *this;
}

const BigInteger BigInteger::operator*(const BigInteger& rhs) const {
  BigInteger result = *this;
  result *= rhs;
  return result;
}

BigInteger& BigInteger::operator/=(const BigInteger& rhs) {
  if (rhs == BigInteger(0))
    throw BigInteger::ArithmeticsException();

  BigInteger b = rhs;
  b.sign = false;
  BigInteger result, current;
  result.poly.resize(poly.size());

  for (int64_t i = int64_t(poly.size()) - 1; i >= 0; i--) {
    current.shright();
    current.poly[0] = poly[i];
    current.trim();
    int digit = 0;
    int left = 0;
    int right = BigInteger::BASE;

    while (left <= right) {
      int middle = (left + right) / 2;
      BigInteger check = b * BigInteger(middle);
      if (check <= current) {
        digit = middle;
        left = middle + 1;
      } else
        right = middle - 1;
    }

    result.poly[i] = digit;
    current = current - b * BigInteger(digit);
  }

  result.sign = sign != rhs.sign;
  result.trim();
  return *this = result;
}

const BigInteger BigInteger::operator/(const BigInteger& rhs) const {
  BigInteger result = *this;
  result /= rhs;
  return result;
}

const BigInteger BigInteger::operator%(const BigInteger& rhs) const {
  BigInteger result = *this;
  result %= rhs;
  return result;
}

BigInteger& BigInteger::operator%=(const BigInteger& rhs) {
  *this -= (*this / rhs) * rhs;
  if (sign)
    *this += rhs;

  return *this;
}

BigInteger::operator bool() const {
  return poly[0] != 0;
}

BigInteger::operator std::string() const {
  std::stringstream ss;
  ss << *this;
  return ss.str();
}