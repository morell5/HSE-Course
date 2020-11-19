#include <iostream>
#include <vector>
#include <string>

struct Multiplicator {
    void simple_multiply(std::vector<int> &a, std::vector<int> &b, std::vector<int> &res) {
        res.resize(a.size() + b.size());
        for(int i = 0; i < b.size(); i++) {
            for(int j = 0; j < a.size(); j++) {
                res[i + j] += b[i] * a[j];
            }
        }
    }
        
    void sum(std::vector<int> &a, std::vector<int> &b, std::vector<int> &res) {
        res.resize(std::max(a.size(), b.size()));
        if(a.size() < b.size()) {
            std::swap(a, b);
        }
        res = a;
        for(int i = 0; i < b.size(); i++) {
            res[i] += b[i];
        }
    }
        
    void decrease(std::vector<int> &a, std::vector<int> &b, std::vector<int> &res) {
        res.resize(std::max(a.size(), b.size()));
        res = a;
        for(int i = 0; i < b.size(); i++) {
            res[i] -= b[i];
        }
    }
        
    void multiply(std::vector<int> &a, std::vector<int> &b, std::vector<int> &res) {
        if(std::max(a.size(), b.size()) < 100) {
            simple_multiply(a, b, res);
            return;
        }
        if(a.size() < b.size()) {
            std::swap(a, b);
        }
    
        while(b.size() < a.size()) {
            b.push_back(0);
        }
        while((b.size() & 1)) {
            a.push_back(0);
            b.push_back(0);
        }
        int mid = a.size() / 2;
        std::vector<int> al, ar, bl, br;
        for(int i = 0; i < a.size(); i++) {
            if(i < mid) {
                al.push_back(a[i]);
                bl.push_back(b[i]);
            }
            else {
                ar.push_back(a[i]);
                br.push_back(b[i]);
            }
        }
        std::vector<int> r1, r2, r3, r4;
        std::vector<int> kl, kr;
        sum(al, ar, kl);
        sum(bl, br, kr);
        multiply(al, bl, r1);
        multiply(kl, kr, r2);
        multiply(ar, br, r4);
        reverse(r1.begin(), r1.end());
        reverse(r2.begin(), r2.end());
        reverse(r4.begin(), r4.end());
        decrease(r2, r1, r3);
        decrease(r3, r4, r2);
        for(int i = 0; i < mid; i++) {
            r2.push_back(0);
        }
        for(int i = 0; i < 2 * mid; i++) {
            r4.push_back(0);
        }
        reverse(r1.begin(), r1.end());
        reverse(r2.begin(), r2.end());
        reverse(r4.begin(), r4.end());
        sum(r1, r2, res);
        std::vector<int> res2;
        sum(res, r4, res2);
        res = res2;
    }
};

class BigInteger {
    private:
        std::vector<int> base;
        bool negative = 0;

    public:

        BigInteger() = default;

        BigInteger(int a) {
            if(a < 0) {
                negative = 1;
            }
            a = abs(a);
            base.clear();
            while(a != 0) {
                base.push_back(a % 10);
                a /= 10;
            }
        }

        void operator=(int a) {
            if(a < 0) {
                negative = 1;
            }
            a = abs(a);
            base.clear();
            while(a != 0) {
                base.push_back(a % 10);
                a /= 10;
            }
        }

        BigInteger& operator+= (BigInteger int2) {
            BigInteger nw = *this + int2;
            base = nw.base;
            negative = nw.negative;
            return *this;
        }

        BigInteger& operator-= (BigInteger int2) {
            BigInteger nw = *this - int2;
            base = nw.base;
            negative = nw.negative;
            return *this;
        }

        BigInteger& operator*= (BigInteger int2) {
            BigInteger nw = *this * int2;
            base = nw.base;
            negative = nw.negative;
            return *this;
        }

        BigInteger& operator/= (BigInteger int2) {
            BigInteger nw = *this / int2;
            base = nw.base;
            negative = nw.negative;
            return *this;
        }

        BigInteger& operator%= (BigInteger int2) {
            BigInteger nw = *this % int2;
            base = nw.base;
            negative = nw.negative;
            return *this;
        }

        BigInteger operator- () {
            negative = !negative;
            return *this;
        }

        BigInteger operator+ (BigInteger int2) {
            int next = 0;
            BigInteger answer;
            BigInteger a = *this;
            BigInteger b = int2;
            if(a.negative == false && b.negative == false) {
                answer.negative = false;
            }
            else if(a.negative == true && b.negative == false) {
                a.negative = false;
                answer = b - a;
                return answer;
            }
            else if(a.negative == false && b.negative == true) {
                b.negative = false;
                answer = a - b;
                return answer;
            }
            else {
                answer.negative = true;
            }
            if(a < b) {
                std::swap(a, b);
            }
            for(int i = 0; i < a.base.size(); i++) {
                if(i < b.base.size()) {
                    int num = a.base[i] + b.base[i] + next;
                    answer.base.push_back(num % 10);
                    next = (num / 10) % 10;
                }
                else {
                    answer.base.push_back(a.base[i] + next);
                    next = 0;
                }
            }
            if(next != 0) {
                answer.base.push_back(next);
            }
            return answer;
        }

        

        BigInteger operator- (BigInteger int2) {
            BigInteger answer;
            BigInteger a = *this;
            BigInteger b = int2;
            if(a.negative == false && b.negative == false) {
                answer.negative = false;
            }
            else if(a.negative == true && b.negative == false) {
                a.negative = false;
                answer = a + b;
                answer.negative = true;
                return answer;
            }
            else if(a.negative == false && b.negative == true) {
                b.negative = false;
                answer = a + b;
                answer.negative = false;
                return answer;
            }
            else {
                std::swap(a, b);
                answer.negative = false;
            }
            int inverse = 0;
            if(a < b) {
                std::swap(a, b);
                inverse = 1;
            }
            int add = 0;
            for(int i = 0; i < a.base.size(); i++) {
                if(i < b.base.size()) {
                    if(a.base[i] - add >= b.base[i]) {
                        answer.base.push_back(a.base[i] - add - b.base[i]);
                        // std::cerr << a.base[i] - add - b.base[i];
                    }
                    else {
                        answer.base.push_back(a.base[i] - add - b.base[i] + 10);
                        // std::cerr << a.base[i] - add - b.base[i] + 10;
                        add = 1;
                    }
                }
                else {
                    if(a.base[i] >= add) {
                        answer.base.push_back(a.base[i] - add);
                        add = 0;
                    }
                    else {
                        answer.base.push_back(10 - add);
                        add = 1;
                    }
                }
            }
            while(answer.base.size() && answer.base.back() == 0) {
                answer.base.pop_back();
            }
            if(answer.base.size() == 0) {
                answer.base.push_back(0);
            }
            answer.negative ^= inverse;
            return answer;
        }

        BigInteger operator* (BigInteger int2) {
            BigInteger a = *this;
            BigInteger b = int2;
            BigInteger answer;
            Multiplicator multiplicator;
            multiplicator.multiply(a.base, b.base, answer.base);
            if(a.negative ^ b.negative) {
                answer.negative = true;
            }
            else {
                answer.negative = false;
            }
            for(int i = 0; i < answer.base.size() - 1; i++) {
                if(i < answer.base.size() - 1) {
                    answer.base[i + 1] += answer.base[i] / 10;
                    answer.base[i] %= 10;
                }
            }
            while(answer.base.back() != 0) {
                int cnt = answer.base.back();
                answer.base[answer.base.size() - 1] %= 10;
                answer.base.push_back(cnt / 10);
                
            }
            while(answer.base.size() && answer.base.back() == 0) {
                answer.base.pop_back();
            }
            if(answer.base.size() == 0) {
                answer.base.push_back(0);
            }
            return answer;
        }

        BigInteger operator/ (BigInteger int2) {
            BigInteger a = *this;
            BigInteger b = int2;
            BigInteger answer;
            if(a.negative ^ b.negative) {
                answer.negative = true;
            }
            else {
                answer.negative = false;
            }
            a.negative = false;
            b.negative = false;
            int pos = a.base.size() - 1;
            BigInteger cur = 0;
            while(pos >= 0) {
                cur = cur * BigInteger(10) + BigInteger(a.base[pos]);
                pos--;
                if(cur >= b) {
                    int num;
                    for(int i = 0; i < 10; i++) {
                        if(b * BigInteger(i) > cur) {
                            num = i - 1;
                            break;
                        }
                    }
                    BigInteger bigNum = num;
                    cur = cur - (b * bigNum);
                    answer.base.push_back(num);
                }
                else {
                    answer.base.push_back(0);
                }
            }
            reverse(answer.base.begin(), answer.base.end());
            while(answer.base.size() && answer.base.back() == 0) {
                answer.base.pop_back();
            }
            if(answer.base.size() == 0) {
                answer.base.push_back(0);
            }
            return answer;
        }

        BigInteger operator% (BigInteger int2) {
            BigInteger a = *this;
            BigInteger b = int2;
            BigInteger answer = a;
            bool negative = a.negative;
            b.negative = false;
            int pos = a.base.size() - 1;
            BigInteger cur = 0;
            while(pos >= 0) {
                cur = cur * BigInteger(10) + BigInteger(a.base[pos]);
                pos--;
                if(cur >= b) {
                    int num;
                    for(int i = 0; i < 10; i++) {
                        if(b * BigInteger(i) > cur) {
                            num = i - 1;
                            break;
                        }
                    }
                    BigInteger bigNum = num;
                    cur = cur - (b * bigNum);
                    answer = cur;
                }
            }
            answer.negative = negative;
            return answer;
        }

        bool operator== (BigInteger int2) {
            if(base.size() != int2.base.size()) {
                return false;
            }
            for(int i = 0; i < base.size(); i++) {
                if(base[i] != int2.base[i]) {
                    return false;
                }
            }
            return true;
        }

        bool operator!= (BigInteger int2) {
            return !(*this == int2);
        }

        bool operator< (BigInteger int2) {
            if(base.size() < int2.base.size()) {
                return true;
            }
            if(base.size() > int2.base.size()) {
                return false;
            }
            for(int i = base.size() - 1; i >= 0; i--) {
                if(base[i] < int2.base[i]) {
                    return true;
                }
                if(base[i] > int2.base[i]) {
                    return false;
                }
            }
            return false;
        }

        bool operator> (BigInteger int2) {
            return !(*this < int2) && *this != int2;
        }

        bool operator<= (BigInteger int2) {
            return !(*this > int2);
        }

        bool operator>= (BigInteger int2) {
            return !(*this < int2);
        }

        BigInteger& operator++() {
            *this = *this + BigInteger(1);
            if(*this >= BigInteger(0)) {
                this->negative = false;
            }
            return *this;
        }

        BigInteger operator++(int) {
            BigInteger current = *this;
            ++*this;
            if(*this >= BigInteger(0)) {
                this->negative = false;
            }
            return current;
        }

        operator bool() const {
            return !(*this == 0);
        }

        std::string toString() {
            std::string ans = "";
            for(int i : base) {
                ans += (i + '0');
            }
            reverse(ans.begin(), ans.end());
            return ans;
        }

        std::vector<int> getBase() {
            return base;
        }

        bool getNegative() {
            return negative;
        }

        // Could be overflow
        int toInt() {
            int ans = 0;
            int pw = 1;
            for(int i = 0; i < base.size(); i++) {
                ans += base[i] * pw;
                pw *= 10;
            }
            return ans;
        }

        friend std::ostringstream& operator<<(std::ostringstream& os, BigInteger &integer);

        friend std::ostream& operator<<(std::ostream& os, BigInteger integer);

};

std::ostringstream& operator<<(std::ostringstream& os, BigInteger &integer) {
    os << ((integer.getNegative()) ? "-" : "");
    for(int i = integer.getBase().size() - 1; i >= 0; i--) {
        os << integer.getBase()[i];
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, BigInteger integer) {
    os << ((integer.getNegative()) ? "-" : "");
    for(int i = integer.getBase().size() - 1; i >= 0; i--) {
        os << integer.getBase()[i];
    }
    return os;
}

std::istringstream& operator>>(std::istringstream& is, BigInteger &integer) {
    std::string s;
    is >> s;
    return is;
}

std::istream& operator>>(std::istream& is, BigInteger integer) {
    std::string s;
    is >> s;
    return is;
}