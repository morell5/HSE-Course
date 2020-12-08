#include <vector> 
#include <string>
#include <iostream>

    class BigInteger {

        public:

        std::vector<int> numb ;
        int zn = 1;

        BigInteger();
	    BigInteger(int);   
        BigInteger(std::string);     

        BigInteger operator+(BigInteger& other);
        BigInteger operator%(BigInteger other);
        BigInteger operator-(BigInteger other);
        BigInteger operator*(BigInteger& other);        
        BigInteger operator/(BigInteger& other);

        BigInteger& operator=(BigInteger other);
        BigInteger& operator=(int other);

        BigInteger& operator++();
        BigInteger operator++(int);
        BigInteger& operator--();
        BigInteger operator--(int);
        BigInteger& operator-();

        BigInteger& operator+=(BigInteger& other);
        BigInteger& operator%=(BigInteger& other);
        BigInteger& operator-=(BigInteger other);
        BigInteger& operator*=(BigInteger& other);        
        BigInteger& operator/=(BigInteger& other);

        bool operator<(BigInteger& other);
        bool operator>(BigInteger& other);
        bool operator==(BigInteger& other);
        bool operator<=(BigInteger& other);
        bool operator>=(BigInteger& other);
        bool operator!=(BigInteger& other);

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