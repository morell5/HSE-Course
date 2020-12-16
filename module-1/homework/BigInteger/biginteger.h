#include <vector> 
#include <string>
#include <iostream>

    class BigInteger {

        private:
            std::vector<int> numb ;
            int zn = 1;

        public:       

        BigInteger();
	    BigInteger(int);   
        BigInteger(std::string);  

        BigInteger& plus(BigInteger& x, const BigInteger& y);
        BigInteger& minus(BigInteger& x, const BigInteger& y);

        BigInteger operator+(const BigInteger& other);
        BigInteger operator%(BigInteger other);
        BigInteger operator-(BigInteger other);
        BigInteger operator*(const BigInteger& other);        
        BigInteger operator/(const BigInteger& other);

        BigInteger& operator=(BigInteger other);
        BigInteger& operator=(int other);

        BigInteger& operator++();
        BigInteger operator++(int);
        BigInteger& operator--();
        BigInteger operator--(int);
        BigInteger& operator-();

        BigInteger& operator+=(const BigInteger& other);
        BigInteger& operator%=(const BigInteger& other);
        BigInteger& operator-=(const BigInteger& other);
        BigInteger& operator*=(const BigInteger& other);        
        BigInteger& operator/=(const BigInteger& other);

        bool operator<(const BigInteger& other);
        bool operator>(const BigInteger& other);
        bool operator==(const BigInteger& other);
        bool operator<=(const BigInteger& other);
        bool operator>=(const BigInteger& other);
        bool operator!=(const BigInteger& other);

        BigInteger& operator=(std::string other);

        operator bool();

        BigInteger operator*(int other);
        BigInteger operator/(int other);
        BigInteger& operator/=(int other);
        BigInteger operator%=(int other);
        BigInteger operator==(int other);


        friend std::ostream& operator<<(std::ostream&, const BigInteger&);
	    friend std::istream& operator>>(std::istream&, BigInteger&);

        std::string toString() const;

    };