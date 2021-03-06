#include <iostream>

auto counter = []() { 
    static int i; 
    return ++i;
};

// the behavior is equivalent to the following class

class Counter {
    public:
        int operator() () const {
            static int i;
            return ++i;
        }
};

int main() {
    auto c1 = counter;
    auto c2 = counter;
    // equivalent to 
    // Counter c1;
    // Counter c2;
    
    std::cout << c1() << c1() << c1() << std::endl;
    std::cout << c2() << c2() << c2() << std::endl;
    return 0;
}