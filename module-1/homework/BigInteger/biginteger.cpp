#include "biginteger.h"

namespace bulumutka {

const int BigInteger::kBase = 100000000;
const int BigInteger::kDigitsNumber = 8;
const BigInteger BigInteger::kZero = 0;
const BigInteger BigInteger::kOne = 1;

BigInteger::BigInteger() : BigInteger("0") {}

BigInteger::BigInteger(int value) : BigInteger(std::to_string(value)) {}

BigInteger::BigInteger(int64_t value) : BigInteger(std::to_string(value)) {}

BigInteger::BigInteger(const std::string& str) : negative_(false) {
    if (str.empty()) {
        data_.push_back(0);
        return;
    }
    if (!internal::IsCorrectStrNumber(str)) {
        throw std::invalid_argument("Invalid format of number");
    }
    if (str[0] == '-') {
        negative_ = true;
    }

    int start_index = 0;
    if (internal::IsSign(str[0])) {
        start_index = 1;
    }

    for (int64_t i = static_cast<int64_t>(str.size()); i > start_index; i -= kDigitsNumber) {
        std::string num;
        if (i < kDigitsNumber) {
            num = str.substr(start_index, i);
        } else {
            num = str.substr(i - kDigitsNumber, kDigitsNumber);
        }
        data_.push_back(std::stoi(num));
    }
    RemoveLeadingZeros_();
}

BigInteger& BigInteger::operator=(const BigInteger& other) {
    data_ = other.data_;
    negative_ = other.negative_;
    return *this;
}

BigInteger& BigInteger::operator=(const std::string& str) {
    *this = BigInteger(str);
    return *this;
}

BigInteger& BigInteger::operator=(int value) {
    *this = BigInteger(value);
    return *this;
}

BigInteger& BigInteger::operator=(int64_t value) {
    *this = BigInteger(value);
    return *this;
}

const BigInteger BigInteger::operator+(const BigInteger& other) const {
    if (negative_ != other.negative_) {
        if (negative_) {
            return other - (-*this);
        }
        return *this - (-other);
    }

    BigInteger result;
    internal::Summation(data_, other.data_, result.data_, kBase);
    result.negative_ = negative_;
    result.RemoveLeadingZeros_();
    return result;
}

const BigInteger BigInteger::operator-(const BigInteger& other) const {
    if (negative_ != other.negative_) {
        if (negative_) {
            return -((-*this) + other);
        }
        return *this + (-other);
    }
    
    if (internal::Compare(data_, other.data_) == 1) {
        return -(other - *this);
    }

    BigInteger result;
    internal::Subtraction(data_, other.data_, result.data_, kBase);
    result.negative_ = negative_;
    result.RemoveLeadingZeros_();
    return result;
}

const BigInteger BigInteger::operator*(const BigInteger& other) const {
    BigInteger result;
    internal::Multiply(data_, other.data_, result.data_, kBase);
    result.negative_ = negative_ != other.negative_;
    result.RemoveLeadingZeros_();
    return result;
}

const BigInteger BigInteger::operator/(const BigInteger& other) const {
    if (other == kZero) {
        throw std::invalid_argument("Can't devide on zero");
    }

    BigInteger copy(other);
    copy.negative_ = false;
    BigInteger result, current;
    result.data_.resize(data_.size());
    for (int i = static_cast<int>(data_.size()) - 1; i >= 0; --i) {
        internal::Shift(current.data_);
        current.data_[0] = data_[i];
        current.RemoveLeadingZeros_();

        const int res = internal::BinarySearch(0, kBase, [&current, &copy](int mid) {
            return copy * BigInteger(mid) <= current;
        });

        result.data_[i] = res;
        current = current - copy * BigInteger(res);
    }
    result.negative_ = other.negative_ != negative_;
    result.RemoveLeadingZeros_();
    return result;
}

const BigInteger BigInteger::operator%(const BigInteger& other) const {
    auto result = *this - (*this / other) * other;
    if (result.negative_) {
        result = result + other;
    }
    return result;
}

const BigInteger BigInteger::operator+() const {
    BigInteger result = *this;
    return result;
}

const BigInteger BigInteger::operator-() const {
    BigInteger result(*this);
    result.negative_ ^= true;
    result.RemoveLeadingZeros_();
    return result;
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
    *this += kOne;
    return *this;
}

BigInteger BigInteger::operator++(int) {
    auto res = *this;
    ++(*this);
    return res;
}

BigInteger& BigInteger::operator--() {
    *this -= kOne;
    return *this;
}

BigInteger BigInteger::operator--(int) {
    auto res = *this;
    --(*this);
    return res; 
}

bool BigInteger::operator==(const BigInteger& other) const {
    return internal::Compare(data_, other.data_) == 0 && 
        negative_ == other.negative_;
}

bool BigInteger::operator!=(const BigInteger& other) const {
    return !(*this == other);
}

bool BigInteger::operator<(const BigInteger& other) const {
    if (negative_ != other.negative_) {
        return negative_;
    }
    int res = internal::Compare(data_, other.data_);
    if (negative_) {
        return res == -1;
    } else {
        return res == 1;
    }
}

bool BigInteger::operator>(const BigInteger& other) const {
    return other < *this;
}

bool BigInteger::operator<=(const BigInteger& other) const {
    return !(other < *this);
}

bool BigInteger::operator>=(const BigInteger& other) const {
    return !(*this < other);
}

BigInteger::operator bool() const {
    return *this != kZero;
}

std::ostream& operator<<(std::ostream& output_stream, const BigInteger& number) {
    output_stream << number.toString();
    return output_stream;
}

std::istream& operator>>(std::istream& input_stream, BigInteger& number) {
    std::string value;
    input_stream >> value;
    number = value;
    return input_stream;
}

std::string BigInteger::toString() const {
    if (*this == kZero) {
        return "0";
    }
    std::string result = "";
    for (auto i : data_) {
        result += internal::ProceedInt(i);
    }
    internal::RemoveTrailingZeros(result);
    result += negative_ ? "-" : "";
    internal::Reverse(result);
    return result;
}

void BigInteger::RemoveLeadingZeros_() {
    while (data_.size() > 1 && data_.back() == 0) {
        data_.pop_back();
    }
    if (data_.size() == 1 && data_[0] == 0) {
        negative_ = false;
    }
}

namespace internal {

template<class T, class F>
T BinarySearch(const T& start, const T& end, const F func) {
    T left = start;
    T right = end;
    T res = left;
    while (left <= right) {
        const T mid = (left + right) / 2;
        if (func(mid)) {
            res = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return res;
}

template<class Collection> 
void Reverse(Collection& data) {
    const int size = static_cast<int>(data.size());
    for (int i = 0; i < size / 2; ++i) {
        std::swap(data[i], data[size - 1 - i]);
    }
}

bool IsSign(char ch) {
    return ch == '-' || ch == '+';
}

bool IsDigit(char ch) {
    return ch >= '0' && ch <= '9'; 
}

bool IsCorrectStrNumber(const std::string& number) {
    if (number.empty()) {
        return true;
    }
    if (!IsSign(number[0]) && !IsDigit(number[0])) {
        return false;
    }
    for (size_t i = 1; i < number.size(); ++i) {
        if (!IsDigit(number[i])) {
            return false;
        }
    }
    return true;
}

void RemoveTrailingZeros(std::string& str) {
    int64_t i = static_cast<int64_t>(str.size()) - 1;
    while (str.size() > 1 && str[i--] == '0') {
        str.pop_back();
    }
}

std::string ProceedInt(int val) {
    auto str = std::to_string(val);
    Reverse(str);
    while (str.size() < 8) {
        str += "0";
    }
    return str;
}

/**
 * Comparator.
 * Returns:
 *      1  - first < second
 *      0  - first == second
 *      -1 - first > second
 */
int Compare(const std::vector<int>& first, const std::vector<int>& second) {
    if (first.size() != second.size()) {
        return first.size() < second.size() ? 1 : -1;
    }

    for (int64_t i = static_cast<int64_t>(first.size()) - 1; i >= 0; --i) {
        if (first[i] != second[i]) {
            return first[i] < second[i] ? 1 : -1;
        }
    }
    return 0;
}

void Summation(const std::vector<int>& first, const std::vector<int>& second,
         std::vector<int>& result, const int base) {
    const size_t max_size = std::max(first.size(), second.size());
    result.clear();
    result.reserve(max_size + 1);
    int mem = 0;
    for (size_t i = 0; i < max_size; ++i) {
        int sum = mem;
        if (i < first.size()) {
            sum += first[i];
        }
        if (i < second.size()) {
            sum += second[i];
        }
        result.push_back(sum % base);
        mem = sum / base;
    }
    result.push_back(mem);
}

void Subtraction(const std::vector<int>& first, const std::vector<int>& second,
         std::vector<int>& result, const int base) {
    result.clear();
    int mem = 0;
    for (size_t i = 0; i < first.size(); i++) {
        int val = first[i] - mem;
        if (i < second.size()) {
            val -= second[i];
        }
        if (val < 0) {
            mem = 1;
            val += base;
        } else {
            mem = 0;
        }
        result.push_back(val);
    }
}

void Multiply(const std::vector<int>& first, const std::vector<int>& second,
              std::vector<int>& result, const int base) {
    result.clear();
    result.resize(first.size() + second.size());
    for (size_t i = 0; i < first.size(); ++i) {
        int mem = 0;
        for (size_t j = 0; j < second.size() || mem != 0; ++j) {
            int64_t value = static_cast<int64_t>(result[i + j]) + mem;
            if (j < second.size()) {
                value += static_cast<int64_t>(first[i]) * second[j];
            }
            result[i + j] = static_cast<int>(value % base);
            mem = static_cast<int>(value / base);
        }
    }
}

void Shift(std::vector<int>& data) {
    if (data.size() == 0) {
        data.push_back(0);
        return;
    }
    data.push_back(data[data.size() - 1]);
    for (int i = static_cast<int>(data.size()) - 2; i > 0; --i) {
        data[i] = data[i - 1];
    }
    data[0] = 0;
}

} // namespace internal

} // namespace bulumutka
