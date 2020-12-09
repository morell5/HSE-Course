#include <iostream>
#include <vector>
#include <string>

struct Multiplicator {
    void simple_multiply(std::vector<int>& a, std::vector<int>& b, std::vector<int>& res) {
        res.resize(a.size() + b.size());
        for(std::size_t i = 0; i < b.size(); i++) {
            for(std::size_t j = 0; j < a.size(); j++) {
                res[i + j] += b[i] * a[j];
            }
        }
    }
        
    void sum(std::vector<int>& a, std::vector<int>& b, std::vector<int>& res) {
        res.resize(std::max(a.size(), b.size()));
        if(a.size() < b.size()) {
            std::swap(a, b);
        }
        res = a;
        for(std::size_t i = 0; i < b.size(); i++) {
            res[i] += b[i];
        }
    }
        
    void decrease(std::vector<int>& a, std::vector<int>& b, std::vector<int>& res) {
        res.resize(std::max(a.size(), b.size()));
        res = a;
        for(std::size_t i = 0; i < b.size(); i++) {
            res[i] -= b[i];
        }
    }

    void prepareNumbers(std::vector<int>& a, std::vector<int>& b, std::vector<int>& res) {
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
    }

    void split(std::vector<int>& al, std::vector<int>& ar, 
                std::vector<int>& bl, std::vector<int>& br, 
                std::vector<int>& a, std::vector<int>& b, int mid) {
        for(std::size_t i = 0; i < a.size(); i++) {
            if(i < mid) {
                al.push_back(a[i]);
                bl.push_back(b[i]);
            }
            else {
                ar.push_back(a[i]);
                br.push_back(b[i]);
            }
        }
    }

    void reverseParts(std::vector<int>& leftToLeftComposition, std::vector<int>& sumToSumComposition, std::vector<int>& rightToRightComposition) {
        reverse(leftToLeftComposition.begin(), leftToLeftComposition.end());
        reverse(sumToSumComposition.begin(), sumToSumComposition.end());
        reverse(rightToRightComposition.begin(), rightToRightComposition.end());
    }

    void multiplyParts(std::vector<int>& leftToLeftComposition, std::vector<int>& sumToSumComposition, 
                        std::vector<int>& rightToRightComposition, std::vector<int>& al,
                        std::vector<int>& bl, std::vector<int>& kl,
                        std::vector<int>& kr, std::vector<int>& ar,
                        std::vector<int>& br) {
        multiply(al, bl, leftToLeftComposition);
        multiply(kl, kr, sumToSumComposition);
        multiply(ar, br, rightToRightComposition);
    }

    void sumParts(std::vector<int>& al, std::vector<int>& bl, 
                    std::vector<int>& kl, std::vector<int>& kr, 
                    std::vector<int>& ar, std::vector<int>& br) {
        sum(al, ar, kl);
        sum(bl, br, kr);
    }
        
    void multiply(std::vector<int>& a, std::vector<int>& b, std::vector<int>& res) {
        if(std::max(a.size(), b.size()) < 100) {
            simple_multiply(a, b, res);
            return;
        }
        prepareNumbers(a, b, res);
        int mid = a.size() / 2;
        std::vector<int> al;
        std::vector<int> ar;
        std::vector<int> bl;
        std::vector<int> br;
        split(al, ar, bl, br, a, b, mid);
        std::vector<int> leftToLeftComposition;
        std::vector<int> sumToSumComposition;
        std::vector<int> sumToLeftDifference;
        std::vector<int> rightToRightComposition;
        std::vector<int> kl;
        std::vector<int> kr;
        sumParts(al, bl, kl, kr, ar, br);
        multiplyParts(leftToLeftComposition, sumToSumComposition, rightToRightComposition, al, bl, kl, kr, ar, br);
        reverseParts(leftToLeftComposition, sumToSumComposition, rightToRightComposition);
        decrease(sumToSumComposition, leftToLeftComposition, sumToLeftDifference);
        decrease(sumToLeftDifference, rightToRightComposition, sumToSumComposition);
        for(std::size_t i = 0; i < mid; i++) {
            sumToSumComposition.push_back(0);
        }
        for(std::size_t i = 0; i < 2 * mid; i++) {
            rightToRightComposition.push_back(0);
        }
        reverseParts(leftToLeftComposition, sumToSumComposition, rightToRightComposition);
        sum(leftToLeftComposition, sumToSumComposition, res);
        std::vector<int> res2;
        sum(res, rightToRightComposition, res2);
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
            base.clear();
            if(a == 0) {
                base.push_back(0);
                return;
            }
            a = abs(a);
            base.clear();
            while(a != 0) {
                base.push_back(a % 10);
                a /= 10;
            }
            normalizeZero();
        }

        BigInteger& operator=(int a) {
            if(a < 0) {
                negative = 1;
            }
            base.clear();
            if(a == 0) {
                base.push_back(0);
                return *this;
            }
            a = abs(a);
            base.clear();
            while(a != 0) {
                base.push_back(a % 10);
                a /= 10;
            }
            return *this;
            normalizeZero();
        }

        BigInteger& operator+= (const BigInteger& int2) {
            BigInteger nw = *this + int2;
            base = nw.base;
            negative = nw.negative;
            normalizeZero();
            return *this;
        }

        BigInteger& operator-= (const BigInteger& int2) {
            BigInteger nw = *this - int2;
            base = nw.base;
            negative = nw.negative;
            normalizeZero();
            return *this;
        }

        BigInteger& operator*= (const BigInteger& int2) {
            BigInteger nw = *this * int2;
            base = nw.base;
            negative = nw.negative;
            normalizeZero();
            return *this;
        }

        BigInteger& operator/= (const BigInteger& int2) {
            BigInteger nw = *this / int2;
            base = nw.base;
            negative = nw.negative;
            normalizeZero();
            return *this;
        }

        BigInteger& operator%= (const BigInteger& int2) {
            BigInteger nw = *this % int2;
            base = nw.base;
            negative = nw.negative;
            normalizeZero();
            return *this;
        }

        BigInteger operator- () {
            negative = !negative;
            normalizeZero();
            return *this;
        }

        BigInteger& operator++() {
            *this = *this + BigInteger(1);
            if(*this >= BigInteger(0)) {
                negative = false;
            }
            return *this;
        }

        BigInteger operator++(int) {
            BigInteger current = *this;
            ++*this;
            if(*this >= BigInteger(0)) {
                negative = false;
            }
            return current;
        }

        operator bool() const {
            return !(BigInteger(*this) == BigInteger(0));
        }

        std::string toString() {
            std::string ans = "";
            for(int i : base) {
                ans += (i + '0');
            }
            reverse(ans.begin(), ans.end());
            return ans;
        }

        std::vector<int> getBase() const {
            return base;
        }

        bool getNegative() const {
            return negative;
        }

        // Could be overflow
        int toInt() {
            int ans = 0;
            int pw = 1;
            for(std::size_t i = 0; i < base.size(); i++) {
                ans += base[i] * pw;
                pw *= 10;
            }
            return ans;
        }

        void normalizeZero() {
            if(this != nullptr && *this == BigInteger(0)) {
                negative = false;
            }
        }

        friend std::ostringstream& operator<<(std::ostringstream& os, const BigInteger& integer);
        friend std::ostream& operator<<(std::ostream& os, const BigInteger& integer);
        friend std::istringstream& operator>>(std::istringstream& is, BigInteger& integer);
        friend bool operator== (const BigInteger& int1, const BigInteger& int2);
        friend bool operator!= (const BigInteger& int1, const BigInteger& int2);
        friend bool operator< (const BigInteger& int1, const BigInteger& int2);
        friend bool isLess(const BigInteger& int1, const BigInteger& int2);
        friend bool operator> (const BigInteger& int1, const BigInteger& int2);
        friend bool operator<= (const BigInteger& int1, const BigInteger& int2);
        friend bool operator>= (const BigInteger& int1, const BigInteger& int2);
        friend BigInteger operator+ (const BigInteger& int1, const BigInteger& int2);
        friend BigInteger operator- (const BigInteger& int1, const BigInteger& int2);
        friend BigInteger operator* (const BigInteger& int1, const BigInteger& int2);
        friend BigInteger operator/ (const BigInteger& int1, const BigInteger& int2);
        friend BigInteger operator% (const BigInteger& int1, const BigInteger& int2);

};

bool isLess(const BigInteger& int1, const BigInteger& int2) {
    if(int1.base.size() < int2.base.size()) {
        return true;
    }
    if(int1.base.size() > int2.base.size()) {
        return false;
    }
    for(std::size_t i = int1.base.size() - 1; i >= 0; i--) {
        if(int1.base[i] < int2.base[i]) {
            return true;
        }
        if(int1.base[i] > int2.base[i]) {
            return false;
        }
        if(i == 0) {
            break;
        }
    }
    return false;
}

bool checkDifferentSignsZeros(const std::vector<int>& base1, const std::vector<int>& base2) {
    return base1.size() == 1 && base1[0] == 0 && base2[0] == 0;
}

bool operator== (const BigInteger& int1, const BigInteger& int2) {
    std::vector<int> base1 = int1.getBase();
    std::vector<int> base2 = int2.getBase();
    if(base1.size() != base2.size()) {
        return false;
    }
    if(checkDifferentSignsZeros(base1, base2)) {
        return true;
    }
    if(int1.negative != int2.negative) {
        return false;
    }
    for(std::size_t i = 0; i < base1.size(); i++) {
        if(base1[i] != base2[i]) {
            return false;
        }
    }
    return true;
}

bool operator!= (const BigInteger& int1, const BigInteger& int2) {
    return !(int1 == int2);
}

std::ostringstream& operator<<(std::ostringstream& os, const BigInteger& integer) {
    os << ((integer.getNegative()) ? "-" : "");
    std::vector<int> base = integer.getBase();
    for(std::size_t i = base.size() - 1; i >= 0; i--) {
        os << base[i];
        if(i == 0) {
            break;
        }
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const BigInteger& integer) {
    os << ((integer.negative) ? "-" : "");
    std::vector<int> base = integer.base;
    std::cerr << base.size() << '\n';
    for(std::size_t i = 0; i < base.size(); i++) {
        os << base[base.size() - 1 - i];
    }
    return os;
}

std::istringstream& operator>>(std::istringstream& is, BigInteger& integer) {
    integer.base.clear();
    std::string s;
    is >> s;
    for(std::size_t i = 0; i < s.size(); i++) {
        integer.base.push_back(s[s.size() - 1 - i] - '0');
    }
    return is;
}

bool operator< (const BigInteger& int1, const BigInteger& int2) {
    if(int1.negative != int2.negative) {
        return ((int1.negative) ? true : false);
    }
    else {
        return (isLess(int1, int2) != int1.negative);
    }
}

bool operator> (const BigInteger& int1, const BigInteger& int2) {
    return !(int1 < int2) && int1 != int2;
}

bool operator<= (const BigInteger& int1, const BigInteger& int2) {
    return !(int1 > int2);
}

bool operator>= (const BigInteger& int1, const BigInteger& int2) {
    return !(int1 < int2);
}

BigInteger operator+ (const BigInteger& int1, const BigInteger& int2) {
    int next = 0;
    BigInteger answer;
    BigInteger a = int1;
    BigInteger b = int2;
    if(a.negative == false && b.negative == false) {
        answer.negative = false;
    }
    else if(a.negative  && !b.negative) {
        a.negative = false;
        answer = b - a;
        return answer;
    }
    else if(!a.negative && b.negative) {
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
    for(std::size_t i = 0; i < a.base.size(); i++) {
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
    answer.normalizeZero();
    return answer;
}

BigInteger operator- (const BigInteger& int1, const BigInteger& int2) {
    BigInteger answer;
    BigInteger a = int1;
    BigInteger b = int2;
    if(a.negative == false && b.negative == false) {
        answer.negative = false;
    }
    else if(a.negative && !b.negative) {
        a.negative = false;
        answer = a + b;
        answer.negative = true;
        return answer;
    }
    else if(!a.negative && b.negative) {
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
    for(std::size_t i = 0; i < a.base.size(); i++) {
        if(i < b.base.size()) {
            if(a.base[i] - add >= b.base[i]) {
                answer.base.push_back(a.base[i] - add - b.base[i]);
            }
            else {
                answer.base.push_back(a.base[i] - add - b.base[i] + 10);
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
    answer.normalizeZero();
    return answer;
}

BigInteger operator* (const BigInteger& int1, const BigInteger& int2) {
    BigInteger a = int1;
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
    for(std::size_t i = 0; i < answer.base.size() - 1; i++) {
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
    answer.normalizeZero();
    return answer;
}

BigInteger operator/ (const BigInteger& int1, const BigInteger& int2) {
    BigInteger a = int1;
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
        std::cerr << cur << '\n';
        cur = cur * BigInteger(10) + BigInteger(a.base[pos]);
        
        pos--;
        if(cur >= b) {
            int num;
            for(int i = 0; i < 10; i++) {
                if((b * BigInteger(i)) > cur) {
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
    answer.normalizeZero();
    return answer;
}

BigInteger operator% (const BigInteger& int1, const BigInteger& int2) {
    BigInteger a = int1;
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
    answer.normalizeZero();
    return answer;
}