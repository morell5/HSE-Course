#include <iostream>

class Int {
public:
    Int(int val) : val_(val) {};

    Int& operator+=(const Int& rhs) {
        val_ += rhs.val_;
        return *this;
    } 

    friend Int operator+(Int& lhs, const Int& rhs);
    friend std::ostream& operator<<(std::ostream& lhs, const Int& rhs);

private:
    int val_;
};

Int operator+(Int& lhs, const Int& rhs) {
    lhs += rhs;
    return lhs;
}

std::ostream& operator<<(std::ostream& lhs, const Int& rhs) {
    lhs << rhs.val_;
    return lhs;
}

int main() {

    Int myInt(2);
    auto non_template_plus = [value=1](int x) { return x + value; };
    // OK!
    std::cout << non_template_plus(2);
    // CE:
    std::cout << non_template_plus(myInt);

    // 1. Template parameter disappeared
    // 2. auto here is an equivalent for template parameter
    auto template_plus = [value=1](auto x) { return x + value; };
     // OK!
    std::cout << template_plus(2);
    // OK!
    std::cout << template_plus(myInt);
    return 0;
}