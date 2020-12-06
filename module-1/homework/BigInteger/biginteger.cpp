#include "biginteger.h"

//stringy
BigInteger& BigInteger::operator=(std::string other){
    this->numb.clear();
    this->zn = 1;
    int k = 0;
    if (other[0] == '-'){
        this->zn = -1;
        k = 1;
    }
    for(int i = other.size(); i >= k; i--){
        this->numb.push_back((int)other[i]-48);
    }
    return *this;
}

BigInteger::BigInteger(std::string str) {
	this->zn = str.size() && str[0] == '-';

	for (int i = str.size(); i > 0; i--) {
		std::string substr = (i < 1) ? str.substr(0, i) : str.substr(i - 1, 1);
		this->numb.push_back(atoi(substr.c_str()));
	}
}

//Copy operatoty
BigInteger::BigInteger(int other){
    *this = other;
}

BigInteger::BigInteger(){

}


//operatoty на интах
BigInteger& BigInteger::operator=(int other){
    if (other == 0){
        this->numb = {0};
        this->zn = 1;
        return *this;
    }
    BigInteger x;
    x.zn = other / abs(other);
    while (other>0){
        x.numb.push_back(other % 10);
        other/=10;
    }
    *this = x;
    return(*this);
    
}

 BigInteger BigInteger::operator%=(int other){
     BigInteger x = other;
     *this = *this % x;
     return (*this);
 }

bool BigInteger::operator==(BigInteger& other){
    return ((this->numb == other.numb) && (this->zn == other.zn));
}

  BigInteger BigInteger::operator==(int other){
     BigInteger x = other;
     return (*this == x);
 }

BigInteger BigInteger::operator/(int other){
    BigInteger x = other;
    *this = *this / x;
    return (*this);
}

BigInteger BigInteger::operator*(int other){
    this->zn *= other / abs(other);
    this->numb.push_back(0);
    int x = 0;
    for(int i = 0; i < this->numb.size();i++){
        this->numb[i] *= other;
        this->numb[i] += x;
        x = this->numb[i] / 10;
        this->numb[i] %= 10;
    }
    while(x > 0){
        this->numb.push_back(0);
        this->numb[this->numb.size()-2] = x % 10;
        x/=10;
    }
    if (this->numb[this->numb.size()] == 0){
        this->numb.pop_back();
    }
    return *this;
}

//Operator =(*,+,-,%,/)
BigInteger& BigInteger::operator/=(int other){
    BigInteger x = other;
    *this/=x;
    return (*this);
}

BigInteger& BigInteger::operator+=(BigInteger& other){
    *this = *this + other;
    return *this;
}

BigInteger& BigInteger::operator/=(BigInteger& other){
    *this = *this / other;
    return *this;
}

BigInteger& BigInteger::operator*=(BigInteger other){
    *this = *this * other;
    return *this;
}

BigInteger& BigInteger::operator-=(BigInteger other){
    *this = *this - other;
    return *this;
}

BigInteger& BigInteger::operator%=(BigInteger& other){
    *this = *this % other;
    return *this;
}

//Simple operatory
BigInteger& BigInteger::operator=(BigInteger other){
    this->numb = other.numb;
    this->zn = other.zn;
    return *this;
}

BigInteger BigInteger::operator*(BigInteger& other){
    BigInteger y, x, z, n2, nl;
    z = *this;
    x = other;
    n2.zn = z.zn * x.zn;
    x.zn = 1;
    z.zn = 1;
    nl.numb.push_back(0);
    x--;
    while (x > nl){
        z +=*this;
        x--;
    }
    z.zn = n2.zn;
    return z;
}

BigInteger BigInteger::operator%(BigInteger other){
    BigInteger x, y, z;
    x.numb = this->numb;
    y.numb = other.numb;
    z.numb = {0};
    if ((x == z) || (z == y)) return z;
    while (x >= y) {
        x = x - y;
    }
    x.zn = this->zn;
    return x;
}

BigInteger BigInteger::operator/(BigInteger& other){
    BigInteger y, x, z;
    z.numb = this->numb;
    x.numb = other.numb;
    y.numb = {0};
    while (z > x){
        z-=x;
        y++;
    }
    return y; 
}

BigInteger BigInteger::operator+(BigInteger& other){
    if (other.zn * this->zn < 0){
            return (*this - other);
    }
    BigInteger x, y;
    if (this->numb.size() > other.numb.size()){
        x = *this;
        y = other;
    } 
    else {
        x = other;
        y = *this;
    }
    x.numb.push_back(0);
    for(int i = 0; i < y.numb.size(); i++){
        x.numb[i]+=y.numb[i];
        if (x.numb[i]>=10){
            x.numb[i] -= 10;
            x.numb[i+1]++;
        }
    }
    for(int i = 0; i < x.numb.size(); i++){
        if (x.numb[i]>=10){
            x.numb[i] -= 10;
            x.numb[i+1]++;
        }
    }
    while (x.numb[x.numb.size()-1] == 0){
        x.numb.pop_back();
    }
    return x;
}

BigInteger BigInteger::operator-(BigInteger other){
    other.zn*=-1;
    BigInteger x, y, z, w;
    if (other.zn * this->zn > 0){
        return (*this + other);
    }
    z.numb = this->numb;
    w.numb = other.numb;
    if (z>w){
        x = *this;
        y = other;
    }
    else{
        y = *this;
        x = other;
    }
    for(int i = 0; i < y.numb.size(); i++){
        x.numb[i]-=y.numb[i];
        if (x.numb[i]<0){
            x.numb[i] += 10;
            x.numb[i+1]--;
        }
    }
    for(int i = 0; i < x.numb.size()-1; i++){
        if (x.numb[i]<0){
            x.numb[i] += 10;
            x.numb[i+1]--;
        }
    }
    while (x.numb.size() > 1 && x.numb[x.numb.size()-1] == 0){
        x.numb.pop_back();
    }
    return x;
}

//Operatory sravneniya
bool BigInteger::operator>(BigInteger& other){
    if (this->zn == 1 && other.zn == -1){
        return true;
    }
    else if (this->zn == -1 && other.zn == 1){
        return false;
    }
    else if (this->zn == -1 && this->numb.size() > other.numb.size()){
        return false;
    }
    else if (this->zn == -1 && this->numb.size() < other.numb.size()){
        return true;
    }
    else if (this->zn == 1 && this->numb.size() > other.numb.size()){
        return true;
    }
    else if (this->zn == 1 && this->numb.size() < other.numb.size()){
        return false;
    }
    bool k = false;
    for(int i =  other.numb.size()-1; i >=0; i--){
        if (this->numb[i]>other.numb[i]){
            k = true;
            break;
        }
        if (this->numb[i]<other.numb[i]){
            break;
        }
    } 
    if (this->zn == -1) k = false;
    return k;   
}

bool BigInteger::operator<(BigInteger& other){
    return (!((*this > other) || (*this==other)));
}

bool BigInteger::operator<=(BigInteger& other){
    return !(*this > other);
}

bool BigInteger::operator>=(BigInteger& other){
    return ((*this > other) || (*this==other));
}

bool BigInteger::operator!=(BigInteger& other){
    return (!(*this == other));    
}

//Unarniye operatory
BigInteger BigInteger::operator--(int){
    BigInteger h, g;
    h.numb = {1};
    g = *this;
    *this -= h;
    return (g);
}

BigInteger& BigInteger::operator--(){
    BigInteger h;
    h.numb = {1};
    return (*this -= h);
}

BigInteger& BigInteger::operator-(){
    this->zn*=-1;
    return *this;
}

BigInteger BigInteger::operator++(int){
    BigInteger h, g;
    h.numb = {1};
    g = *this;
    *this += h;
    return (g);
}

BigInteger& BigInteger::operator++() {
    BigInteger h;
    h.numb = {1};
	return (*this += h);
}


//Other operatory
BigInteger::operator bool(){  
    BigInteger h;
    h.numb = {0};
    return (*this == h) ? false : true;
}

std::string BigInteger::toString() const {
	std::string str = (this->zn == -1) ? "-" : "";
	for (int i = this->numb.size() - 1; i >= 0; i--) {
		str += std::to_string(this->numb[i]);
	}
	return str;
}

std::ostream& operator<<(std::ostream& out, const BigInteger& x) {
	if (x.zn == -1) out << "-";

	for(int i = x.numb.size()-1; i>=0; i--){
        out<<x.numb[i];
    }

	return out;
}

std::istream& operator>>(std::istream& in, BigInteger& x) {
	std::string str;
	in >> str;
    if (str.size() == 0){
        x.numb = {0};
    }
    else{
        x = BigInteger(str);
    }
	return in;
}