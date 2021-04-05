#include "biginteger.h"
#include <iostream>

BigInteger::BigInteger() {
    clear();
    sign = NEUTRAL;
    big_number.push_back(0);
}

BigInteger::BigInteger(int num) {
    clear();
    if (num == 0) {
        sign = NEUTRAL;
        big_number.push_back(0);
    }
    else {
        if (num < 0) {
            sign = NEGATIVE;
            num = -num;
        } else 
            sign = POSITIVE;
        big_number.push_back(num % MAX_VALUE);
        big_number.push_back(num / MAX_VALUE);
    }
    clear_back();
}

BigInteger::BigInteger(const std::string& num) {
    clear();
    if (!check_string_to_num(num)) {
        sign = NEUTRAL;
        big_number.push_back(0);
    } else {
        int end_of_num = 0;
        sign = POSITIVE;
        if (num[0] == '-') {
            sign = NEGATIVE;
            end_of_num++;
        }
        if (num[0] == '+')
            end_of_num++;
        int cur_pos = num.size() - 1;
        int cur_pos_in_part = 1;
        int num_part = 0;
        while (cur_pos >= end_of_num) {
            if (cur_pos_in_part == MAX_VALUE) {
                big_number.push_back(num_part);
                num_part = 0;
                cur_pos_in_part = 1;
            }
            num_part += static_cast<int>(num[cur_pos] - '0') * cur_pos_in_part;
            cur_pos_in_part *= 10;
            cur_pos--;
        }
        if (cur_pos_in_part > 1)
            big_number.push_back(num_part);
        clear_back();
    }
}

bool BigInteger::is_negative() const {
    return (this->sign == NEGATIVE);
}

bool BigInteger::is_positive() const {
    return (this->sign == POSITIVE);
}

bool BigInteger::is_neutral() const {
    return (this->sign == NEUTRAL);
}


BigInteger::BigInteger(const char s, const std::vector<int>& big_num) {
    sign = s;
    big_number = big_num;
}

bool BigInteger::check_string_to_num(const std::string& input) const {
    if (input.size() == 0)
        return 0;
    size_t i = 0;
    if (input[i] == '-' || input[i] == '+')
        i++;
    int cnt = 0;
    for (i; i < input.size(); i++) {
        if (!(input[i] >= '0' && input[i] <= '9'))
            return false;
        cnt++;
    }
    if (cnt > 0)
        return true;
    return false;
}

void BigInteger::clear() {
    sign = NEUTRAL;
    big_number.clear();
}

std::string BigInteger::toString() const {
    std::string answer;
    if (is_negative())
        answer.push_back('-');
    for (int i = big_number.size() - 1; i >= 0; i--) {
        if (i != big_number.size() - 1) {
            int cur_num = big_number[i];
            if (cur_num == 0)
                for (int i = 0; i < POS_IN_MAX_VALUE - 1; i++)
                    answer.push_back('0');
            else
                while (cur_num < MAX_VALUE / 10) {
                    cur_num *= 10;
                    answer.push_back('0');
                }
        }
        answer += std::to_string(big_number[i]);
    }
    return answer;
}

void BigInteger::clear_back() {
    while (big_number.size() > 1 && big_number[big_number.size() - 1] == 0)
        big_number.pop_back();
    if (big_number.size() == 1 && big_number[0] == 0)
        sign = NEUTRAL;
}

BigInteger& BigInteger::operator=(const BigInteger& big_num) {
    big_number = big_num.big_number;
    sign = big_num.sign;
    return *this;
}

BigInteger& BigInteger::operator=(int num) {
    *this = BigInteger(num);
    return *this;
}

BigInteger& BigInteger::operator=(const std::string& num) {
    *this = BigInteger(num);
    return *this;
}

bool operator==(const BigInteger& left, const BigInteger& right) {
    if (left.sign != right.sign || left.big_number.size() != right.big_number.size())
        return false;
    for (int i = 0; i < left.big_number.size(); i++)
        if (left.big_number[i] != right.big_number[i])
            return false;
    return true;
}

bool operator!=(const BigInteger& left, const BigInteger& right) {
    return !(left == right);
}

bool operator<(const BigInteger& left, const BigInteger& right) {
    if (left.is_negative() && right.is_negative())
        return (-right) < (-left);
    if (left.is_negative() && !right.is_negative())
        return true;
    if (!left.is_negative() && right.is_negative())
        return false;
    if (right.big_number.size() > left.big_number.size())
        return true;
    if (right.big_number.size() < left.big_number.size())
        return false;
    for (int i = left.big_number.size() - 1; i >= 0 ; i--) {
        if (left.big_number[i] < right.big_number[i])
            return true;
        if (left.big_number[i] > right.big_number[i])
            return false;
    }
    return false;
}

bool operator>(const BigInteger& left, const BigInteger& right) {
    return (right < left);
}

bool operator<=(const BigInteger& left, const BigInteger& right) {
    return (left == right || left < right);
}

bool operator>=(const BigInteger& left, const BigInteger& right) {
    return (left == right || left > right);
}

BigInteger& BigInteger::operator-() const{
    if (is_negative())
        return *(new BigInteger(POSITIVE, big_number));
    if (is_positive())
        return *(new BigInteger(NEGATIVE, big_number));
    return *(new BigInteger(NEUTRAL, big_number));
}

BigInteger operator-(const BigInteger& left, const BigInteger& right) {
    if (left.is_negative() && !right.is_negative())
        return -((-left) + right);
    if (!left.is_negative() && right.is_negative())
        return (left + (-right));
    if (left.is_negative() && right.is_negative()) 
        return (-right) - (-left);
    if (right > left)
        return -(right - left);
    int carry = 0;
    BigInteger answer;
    answer.clear();
    answer.sign = BigInteger::POSITIVE;
    for (int i = 0; i < right.big_number.size(); i++) {
        int step_ans = left.big_number[i] - right.big_number[i] - carry;
        carry = 0;
        if (step_ans < 0) {
            step_ans += BigInteger::MAX_VALUE;
            carry = 1;
        }
        answer.big_number.push_back(step_ans);
    }
    for (int i = right.big_number.size(); i < left.big_number.size() || carry != 0; i++) {
        int step_ans = left.big_number[i] - carry;
        carry = 0;
        if (step_ans < 0) {
            step_ans += BigInteger::MAX_VALUE;
            carry = 1;
        }
        answer.big_number.push_back(step_ans);
    }
    answer.clear_back();
    return answer;
}

BigInteger operator+(const BigInteger& left, const BigInteger& right) {
    if (left > right)
        return right + left;
    if (left.is_negative() && !right.is_negative()) 
        return right - (-left);
    if (left.is_negative() && right.is_negative())
        return -((-left) + (-right));
    BigInteger answer;
    int carry = 0;
    answer.clear();
    answer.sign = BigInteger::POSITIVE;
    for (size_t i = 0; i < left.big_number.size(); i++) {
        int step_ans = carry + left.big_number[i] + right.big_number[i];
        carry = step_ans / BigInteger::MAX_VALUE;
        step_ans %= BigInteger::MAX_VALUE;
        answer.big_number.push_back(step_ans);
    }
    for (size_t i = left.big_number.size(); i < right.big_number.size(); i++) {
        int step_ans = carry + right.big_number[i];
        carry = step_ans / BigInteger::MAX_VALUE;
        step_ans %= BigInteger::MAX_VALUE;
        answer.big_number.push_back(step_ans);
    }
    answer.big_number.push_back(carry);
    answer.clear_back();
    return answer;
}

BigInteger operator*(const BigInteger& left, const BigInteger& right) {
    if (left.is_neutral() || right.is_neutral())
        return BigInteger();
    std::vector<int> ans_num(left.big_number.size() + right.big_number.size());
    for (size_t i = 0; i < left.big_number.size(); i++) {
        int carry = 0;
        for (int j = 0; j < right.big_number.size() || carry > 0; j++) {
            long long step_ans = ans_num[i + j] + 
                (j >= right.big_number.size() ? 0 : static_cast<long long>(left.big_number[i]) * right.big_number[j]) 
                + carry;
            carry = step_ans / BigInteger::MAX_VALUE;
            step_ans %= BigInteger::MAX_VALUE;
            ans_num[i + j] = static_cast<int>(step_ans);
        }
    }
    BigInteger answer = BigInteger(BigInteger::NEGATIVE, ans_num);
    if ((!left.is_negative() && !right.is_negative()) ||
        (left.is_negative() && right.is_negative()))
        answer.sign = BigInteger::POSITIVE;
    answer.clear_back();
    return answer;
}

BigInteger BigInteger::abs(const BigInteger& big_num) {
    BigInteger ans = big_num;
    if (ans.sign == NEGATIVE)
        ans.sign = POSITIVE;
    return ans;
}

BigInteger BigInteger::division(const BigInteger& left, const BigInteger& right, bool is_div) {
    if (right.is_neutral())
        throw std::overflow_error("Division by zero!");
    BigInteger divider = abs(right);
    std::vector<int> ans_num(left.big_number.size());
    BigInteger cur_ans;
    for (int i = left.big_number.size() - 1; i >= 0; i--) {
        for (int j = cur_ans.big_number.size() - 1; j > 0; j--)
            cur_ans.big_number[j] = cur_ans.big_number[j - 1];
        cur_ans.clear_back();
        cur_ans.sign = POSITIVE;
        cur_ans.big_number[0] = left.big_number[i];
        int div_res = 0;
        int l = -1, r = MAX_VALUE + 1;
        BigInteger pr_res;
        while (r - l > 1) {
            int m = (l + r) / 2;
            pr_res = divider;
            pr_res *= m;
            if (pr_res > cur_ans)
                r = m;
            else 
                l = m;
        }
        ans_num[i] = l;
        pr_res = divider;
        pr_res *= l;
        cur_ans -= pr_res;
        cur_ans.big_number.push_back(0);
    }
    char ans_sign = POSITIVE;
    if ((left.is_negative() && !right.is_negative()) || (!left.is_negative() && right.is_negative()))
        ans_sign = NEGATIVE;
    BigInteger ans(ans_sign, ans_num);
    ans.clear_back();
    if (is_div)
        return ans;
    else {
        ans *= right;
        return left - ans;
    }
}

BigInteger operator/(const BigInteger& left, const BigInteger& right) {
    return BigInteger::division(left, right, 1);
}

BigInteger operator%(const BigInteger& left, const BigInteger& right) {
    return BigInteger::division(left, right, 0);
}

BigInteger& BigInteger::operator+=(const BigInteger& right) {
    *this = (*this + right);
    return *this;
}

BigInteger& BigInteger::operator-=(const BigInteger& right) {
    *this = (*this - right);
    return *this;
}

BigInteger& BigInteger::operator*=(const BigInteger& right) {
    *this = (*this * right);
    return *this;
}

BigInteger& BigInteger::operator/=(const BigInteger& right) {
    *this = (*this / right);
    return *this;
}

BigInteger& BigInteger::operator%=(const BigInteger& right) {
    *this = (*this % right);
    return *this;
}

std::istream& operator>>(std::istream& in, BigInteger& big_num) {
    std::string input;
    in >> input;
    big_num = input;
    return in;
}

std::ostream& operator<<(std::ostream& out, const BigInteger& big_num) {
    out << big_num.toString();
    return out;
}

BigInteger::operator bool() const {
    return sign != NEUTRAL;
}

BigInteger& BigInteger::operator++() {
    BigInteger one = 1;
    *this = *this + one;
    return *this;
}

BigInteger& BigInteger::operator--() {
    BigInteger one = 1;
    *this = *this - one;
    return *this;
}

BigInteger BigInteger::operator++(int) {
    BigInteger ret = *this;
    ++(*this);
    return ret;
}

BigInteger BigInteger::operator--(int) {
    BigInteger ret = *this;
    --(*this);
    return ret;
}