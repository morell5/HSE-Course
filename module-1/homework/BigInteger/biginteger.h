#include <iostream>
#include <vector>
#include <string>

class BigInteger
{
private:
    BigInteger(std::vector<int> arr); // конструктор положительного числа из массива data - служебный
    std::vector<int> data;            // само число будем хранить в векторе
    bool negative_flag;               // флаг отрицательности числа
    void remove_zeros();              // служебная функция - удаляет ведущие нули.
    const BigInteger baseinn(int n);  //служебная функция - возвращает число, умноженное на BASE^n

public:
    static const int BASE = 1e4;    // основание системы счисления - степень десятки
    static const int SIZE = 4;      // столько знаков будем хранить в одном разряде
    BigInteger();                   // стандартный конструктор
    BigInteger(int number);         // конструктор из int
    BigInteger(std::string number); // конструктор из строки
    operator bool() const;          // неявное преобразование в bool

    std::string toString(); // преобразование в строку

    //std::vector<int> get_data() const; // возвращает массив с разрядами числа
    //bool get_negative() const;         // возвращает флаг отрицательности

    BigInteger &operator=(const BigInteger &other);                                 // оператор присваивания
    BigInteger &operator+=(const BigInteger &other);                                // оператор присваивания сложения
    BigInteger &operator-=(const BigInteger &other);                                // оператор присванивания вычитания
    BigInteger &operator*=(const BigInteger &other);                                // оператор присваивания умножения
    BigInteger &operator/=(const BigInteger &other);                                // оператор присваивания деления
    BigInteger &operator%=(const BigInteger &other);                                // оператор присваивания остатка
    const BigInteger operator-() const;                                             // унарный минус
    BigInteger &operator++();                                                       // префиксный инкремент
    const BigInteger operator++(int);                                               // постфиксный инкремент
    BigInteger &operator--();                                                       // префиксный декремент
    const BigInteger operator--(int);                                               // постфиксный декремент
    friend std::istream &operator>>(std::istream &in, BigInteger &to_);             // оператор ввода
    friend std::ostream &operator<<(std::ostream &out, const BigInteger &printing); // оператор вывода
    friend bool operator==(const BigInteger &a, const BigInteger &b);               // оператор проверки равенства
    friend bool operator!=(const BigInteger &a, const BigInteger &b);               // оператор "не равно"
    friend bool operator<(const BigInteger &a, const BigInteger &b);                // оператор "меньше"
    friend bool operator<=(const BigInteger &a, const BigInteger &b);               // оператор "меньше или равно"
    friend bool operator>(const BigInteger &a, const BigInteger &b);                // оператор "больше"
    friend bool operator>=(const BigInteger &a, const BigInteger &b);               // оператор "больше или равно"
    friend const BigInteger operator+(BigInteger a, const BigInteger &b);           // оператор сложения
    friend const BigInteger operator-(BigInteger a, const BigInteger &b);           // оператор вычитания
    friend const BigInteger operator*(const BigInteger &a, const BigInteger &b);    // оператор умножения
    friend const BigInteger operator/(const BigInteger &a, const BigInteger &b);    // оператор деления
    friend const BigInteger operator%(const BigInteger &a, const BigInteger &b);    // взятие остатка
};