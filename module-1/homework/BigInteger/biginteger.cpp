#include "biginteger.h"

// function to_vector -> to_string
std::string BigInteger::toString()
{
    to_string = "";
    for (int i = 0; i < to_vector.size(); i++)
    {
        if (i != to_vector.size() - 1)
        {   // first part of number
            for (int num = to_vector[i]; num != 1; num /= 10)
            {
                to_string = char(num % 10 + '0') + to_string;
            }
        }
        else
        {   // last part of number
            for (int num = to_vector[i] - max_num; num != 0; num /= 10)
            {
                to_string = char(num % 10 + '0') + to_string;
            }
        }

    }
    return to_string;
}

// function to_string -> to_vector
std::vector<int> BigInteger::toVector()
{
    LL num_now = 0; // variable for one part of number
    LL ten_power = 1; // power of ten
    int counter_signs = 0; // part of number includes only 10 signs
    to_vector.clear();
    sign = 1;
    for (int i = to_string.size() - 1; i >= 0; i--) // convert string to vector
    {
        if (to_string[i] == '-') { // check sign before number
            sign = 0;
            break;
        }
        num_now = num_now + (to_string[i] - '0') * ten_power;
        ten_power *= 10;
        counter_signs++;
        if (counter_signs == 9) // finish to build part of number
        {
            to_vector.push_back(num_now + max_num); // add new part of number to vector
            counter_signs = 0;
            num_now = 0;
            ten_power = 1;
        }
    }
    if (num_now != 0 || num_now == 0 && to_vector.size() == 0)
    {
        to_vector.push_back(num_now + max_num); // add last part to vector
    }
    return to_vector;
}

// convert int to BigInteger
BigInteger& BigInteger::operator = (const int& number_int) // convert int to BigInteger
{
    int new_number_int = number_int;
    if (number_int < 0)
    {
        sign = 0;
        new_number_int *= (-1);
    }
    else
    {
        sign = 1;
    }
    to_vector.clear();
    if (number_int < max_num)
    {
        to_vector.push_back(new_number_int + max_num);
    }
    else
    {
        to_vector.push_back(new_number_int % max_num + max_num);
        to_vector.push_back(new_number_int / max_num + max_num);
    }
    return *this;
}

// convert long long to BigInteger
BigInteger& BigInteger::operator = (const long long& number) // convert int to BigInteger
{
    long long new_number_long = number;
    if (number < 0)
    {
        this->sign = 0;
        new_number_long *= (-1);
    }
    else
    {
        this->sign = 1;
    }
    this->to_vector.clear();
    for (long long i = new_number_long; i != 0; i /= max_num)
    {
        this->to_vector.push_back(i % max_num + max_num);
    }
    return *this;
}

// convert to bool
BigInteger::operator bool() const
{
    if (this->to_vector.size() != 1 || this->to_vector.size() == 1 && this->to_vector[0] != max_num)
    {
        return true;
    }
    return false;
}


// constructors
BigInteger::BigInteger(const int value)
{
    *this = value;
}

BigInteger::BigInteger(const long long value)
{
    *this = value;
}

BigInteger::BigInteger()
{
    to_vector.clear();
    to_string = "";
    sign = 1;
    value = 0;
}


// logical operations
const bool BigInteger::operator == (const BigInteger& number_2)
{
    if (this->to_vector.size() != number_2.to_vector.size() || this->sign != number_2.sign)
    {
        return false;
    }
    for (int i = this->to_vector.size() - 1; i >= 0; i--) // compare of numbers
    {
        if (this->to_vector[i] != number_2.to_vector[i])
        {
            return false;
        }
    }
    return true;
}

const bool BigInteger::operator < (const BigInteger& number_2)
{
    if (this->sign == number_2.sign)
    {
        if (this->to_vector.size() < number_2.to_vector.size())
        {
            if (this->sign)
            {
                return true;
            }
            return false;
        }
        if (this->to_vector.size() > number_2.to_vector.size())
        {
            if (this->sign)
            {
                return false;
            }
            return true;
        }
        int numbers_size = this->to_vector.size();
        for (int i = numbers_size - 1; i >= 0; i--)
        {
            if (this->to_vector[i] < number_2.to_vector[i])
            {
                if (this->sign)
                {
                    return true;
                }
                return false;
            }
            if (this->to_vector[i] > number_2.to_vector[i])
            {
                if (this->sign)
                {
                    return false;
                }
                return true;
            }
        }
        return false;
    }
    else if (this->sign == 0 && number_2.sign == 1)
    {
        return true;
    }
    else if (this->sign == 1 && number_2.sign == 0)
    {
        return false;
    }
}

const bool BigInteger::operator <= (const BigInteger& number_2)
{
    if (*this < number_2 || *this == number_2)
    {
        return true;
    }
    return false;
}

const bool BigInteger::operator > (const BigInteger& number_2)
{
    if (*this <= number_2)
    {
        return false;
    }
    return true;
}

const bool BigInteger::operator >= (const BigInteger& number_2)
{
    if (*this < number_2)
    {
        return false;
    }
    return true;
}

const bool BigInteger::operator != (const BigInteger& number_2)
{
    if (*this == number_2)
    {
        return false;
    }
    return true;
}

// input | output
std::ostream& operator << (std::ostream& out, const BigInteger& number)
{
    BigInteger num = number;
    BigInteger zero = 0;
    num.toString();
    std::string res = num.to_string;
    if (res.size() == 0)
        res = "0";
    //std :: cout << 1 << std :: endl;
    if (!number.sign && res != "0")
    {
        res = "-" + res;
    }
    out << res;
    return out;
}

std::istream& operator >> (std::istream& in, BigInteger& number)
{
    in >> number.to_string;
    number.toVector();
    return in;
}

// operations with BigInteger
BigInteger BigInteger::operator + (BigInteger& number_2)
{
    BigInteger number_1 = *this;
    return (number_1 += number_2);
}

BigInteger BigInteger::operator * (BigInteger& number_2)
{
    BigInteger copy_1 = *this;
    BigInteger copy_2 = number_2;
    BigInteger way;
    way.sign = true;
    BigInteger result;
    result.sign = 1;
    result = 0;
    copy_1.toString();
    copy_2.toString();
    if (copy_1.to_string == "0" || copy_2.to_string == "0")
    {
        result = 0;
        return result;
    }
    std::string zero = "";
    for (int i = copy_2.to_string.size() - 1; i >= 0; i--)
    {
        way.to_string = "";
        int ost = 0;
        for (int j = copy_1.to_string.size() - 1; j >= 0; j--)
        {
            ost = ost + (copy_1.to_string[j] - '0') * (copy_2.to_string[i] - '0');
            way.to_string = char(ost % 10 + '0') + way.to_string;
            ost /= 10;
        }
        if (ost != 0)
        {
            way.to_string = char(ost + '0') + way.to_string;
        }
        way.to_string += zero;
        way.toVector();
        result = result + way;
        zero += '0';
    }
    if (!this->sign && !number_2.sign || this->sign && number_2.sign)
    {
        result.sign = true;
    }
    else
    {
        result.sign = false;
    }
    return result;
}

BigInteger BigInteger::operator - (BigInteger& number_2)
{
    BigInteger number_1 = *this;
    return (number_1 -= number_2);
}

BigInteger BigInteger::operator / (BigInteger& number_2)
{
    BigInteger result;
    BigInteger first = *this;
    BigInteger second = number_2;
    result.to_string = "";
    first.toString();
    second.toString();
    first.sign = true;
    second.sign = true;
    if (first < second)
    {
        result = 0;
        return result;
    }
    BigInteger part_dividend;
    part_dividend.to_string = "";
    part_dividend.sign = true;
    int quotient = 0;
    //std :: cout << first << std :: endl;
    for (int i = 0; i < first.to_string.size(); i++) {
        part_dividend.to_string += first.to_string[i];
        part_dividend.toVector();
        //  std::cout << part_dividend << std::endl;
        quotient = 0;
        //std :: cout << part_dividend << ' ' << std :: endl;
        while (part_dividend >= second) {
            part_dividend = part_dividend - second;
            //std :: cout << "qq " << part_dividend << std :: endl;
            quotient++;
        }
        part_dividend.toString();
        if (!(quotient == 0 && result.to_string.size() == 0))
        {
            result.to_string = result.to_string + char(quotient + '0');
            // std :: cout << "yes\n";
        }
    }
    result.toVector();
    if (this->sign == 1 && number_2.sign == 1 || this->sign == 0 && number_2.sign == 0)
    {
        result.sign = true;
    }
    else
    {
        result.sign = false;
    }
    //std::cout << result.sign << ' ' << result.to_string << ' ' << result.to_vector.size() << std::endl;
    const BigInteger res = result;
    //std::cout << "good";
    return res;

}

BigInteger BigInteger::operator % (BigInteger& number_2)
{
    BigInteger result;
    BigInteger first = *this;
    BigInteger second = number_2;
    result.to_string = "";
    first.sign = true;
    second.sign = true;
    first.toString();
    second.toString();
    if (first < second)
    {
        result = first;
        return result;
    }
    BigInteger part_dividend;
    part_dividend.to_string = "";
    part_dividend.sign = true;
    int quotient = 0;
    for (int i = 0; i < first.to_string.size(); i++) {
        part_dividend.to_string += first.to_string[i];
        part_dividend.toVector();
        quotient = 0;
        while (part_dividend >= second) {
            part_dividend = part_dividend - second;
            quotient++;
        }
        part_dividend.toString();
    }
    if (part_dividend.to_string.size() == 0)
    {
        part_dividend.to_string = "0";
    }
    part_dividend.toVector();
    if (this->sign == 0 && number_2.sign == 1)
    {
        part_dividend = number_2 - part_dividend;

    }
    return part_dividend;
}

BigInteger& BigInteger::operator += (BigInteger number_2)
{
    BigInteger number_1 = *this;
    if (number_1.sign == 1 && number_2.sign == 1)
    {
        this->to_vector.clear();
        LL new_sum;
        LL ost = 0;
        for (int i = 0; i < number_1.to_vector.size() || i < number_2.to_vector.size(); i++)
        {
            new_sum = ost;
            if (i < number_1.to_vector.size())
            {
                new_sum = new_sum + number_1.to_vector[i] - max_num;
            }
            if (i < number_2.to_vector.size())
            {
                new_sum = new_sum + number_2.to_vector[i] - max_num;
            }
            ost = new_sum / max_num;
            this->to_vector.push_back((new_sum % max_num) + max_num);
        }
        if (ost != 0) {
            this->to_vector.push_back(ost);
        }
        this->sign = 1;
        return *this;
    }
    else if (number_1.sign == 1 && number_2.sign == 0)
    {
        this->to_vector.clear();
        BigInteger copy_2 = number_2;
        copy_2.sign = 1;
        *this = number_1 - copy_2;
        return *this;
    }
    else if (number_1.sign == 0 && number_2.sign == 1)
    {
        this->sign = 1;
        *this -= number_2;
        this->sign = ((this->sign + 1) % 2);
        return *this;
    }
    else
    {
        this->to_vector.clear();
        BigInteger copy_1 = number_1;
        BigInteger copy_2 = number_2;
        copy_1.sign = 1;
        copy_2.sign = 1;
        *this = copy_1 + copy_2;
        this->sign = 0;
        return *this;
    }
}

BigInteger& BigInteger::operator -= (BigInteger number_2)
{
    // make copy of numbers
    BigInteger copy_1 = *this;
    BigInteger copy_2 = number_2;
    // check signs
    if (copy_1.sign == 0 && copy_2.sign == 1)
    {
        this->to_vector.clear();
        copy_1.sign = 1;
        copy_2.sign = 1;
        *this = copy_1 + copy_2;
        this->sign = 0;
        return *this;
    }
    else if (copy_1.sign == 1 && copy_2.sign == 1)
    {
        this->to_vector.clear();
        this->sign = 1;
        if (copy_1 < copy_2)
        {
            *this = copy_2 - copy_1;
            this->sign = 0;
            return *this;
        }
        if (copy_1 == copy_2) {
            *this = 0;
            return *this;
        }
        int part_1, part_2, res, ost = 0;
        for (int i = 0; i < copy_1.to_vector.size(); i++)
        {
            part_1 = copy_1.to_vector[i] - max_num;
            part_2 = 0;
            if (i < copy_2.to_vector.size())
            {
                part_2 = copy_2.to_vector[i] - max_num;
            }
            part_1 = part_1 - part_2 - ost;
            if (part_1 < 0)
            {
                part_1 += max_num;
                ost = 1;
            }
            else {
                ost = 0;
            }
            part_1 += max_num;
            this->to_vector.push_back(part_1);
        }
        int result_siz = this->to_vector.size();
        while (this->to_vector[result_siz - 1] == max_num && result_siz != 1)
        {
            this->to_vector.pop_back();
            result_siz--;
        }
        return *this;
    }
    else if (copy_1.sign == 1 && copy_2.sign == 0)
    {
        
        number_2.sign = 1;
        *this += number_2;
        return *this;
    }
    else
    {
        this->sign = 1;
        number_2.sign = 1;
        *this -= number_2;
        this->sign = ((this->sign + 1) % 2);
        return *this;
    }
}

BigInteger& BigInteger::operator *= (BigInteger number_2)
{
    *this = *this * number_2;
    return *this;
}

BigInteger& BigInteger::operator /= (BigInteger number_2)
{
    *this = *this / number_2;
    return *this;
}

BigInteger& BigInteger::operator %= (BigInteger number_2)
{
    *this = *this % number_2;
    return *this;
}

// unarn operations
BigInteger& BigInteger::operator ++ ()
{
    for (int i = 0; i < this->to_vector.size(); i++)
    {
        if (this->to_vector[i] - max_num + 1 >= max_num)
        {
            this->to_vector[i] = max_num;
        }
        else
        {
            this->to_vector[i]++;
            break;
        }
        if (i == this->to_vector.size() - 1)
        {
            this->to_vector.push_back(max_num + 1);
        }
    }
    return *this;
}

BigInteger BigInteger::operator ++ (int)
{
    BigInteger old_number = *this;
    ++(*this);
    return old_number;
}

BigInteger& BigInteger::operator -- ()
{
    for (int i = 0; i < this->to_vector.size(); i++)
    {
        if (this->to_vector[i] == max_num) {
            this->to_vector[i] = max_num - 1 + max_num;
        }
        else
        {
            this->to_vector[i] -= 1;
            break;
        }
    }
    return *this;
}

BigInteger BigInteger::operator -- (int)
{
    BigInteger old_number;
    old_number = *this;
    --(*this);
    return old_number;
}

BigInteger& BigInteger::operator - ()
{
    if (this->sign)
    {
        this->sign = false;
    }
    else
    {
        this->sign = true;
    }
    return *this;
}

// operations with integer
BigInteger BigInteger::operator + (const int& Const)
{
    BigInteger number = *this;
    return (number += Const);
}

BigInteger BigInteger::operator - (const int& Const)
{
    BigInteger number = *this;
    return (number -= Const);
}

BigInteger BigInteger::operator * (const int& Const)
{
    BigInteger number = *this;
    return (number *= Const);
}

BigInteger BigInteger::operator / (const int& Const)
{
    BigInteger number = *this;
    return (number /= Const);
}

BigInteger BigInteger::operator % (const int& Const)
{
    BigInteger number = *this;
    return (number %= Const);
}

BigInteger BigInteger::operator += (const int& Const)
{
    BigInteger number = Const;
    return (*this += number);
}

BigInteger BigInteger::operator -= (const int& Const)
{
    BigInteger number = Const;
    return (*this -= number);
}

BigInteger BigInteger::operator *= (const int& Const)
{
    BigInteger number = Const;
    return (*this *= number);
}

BigInteger BigInteger::operator /= (const int& Const)
{
    BigInteger number = Const;
    return (*this /= number);
}

BigInteger BigInteger::operator %= (const int& Const)
{
    BigInteger number = Const;
    return (*this %= number);
}
