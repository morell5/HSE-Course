#include <iostream>

class Container {
    public:
    Container() = default;
    Container(const Container& other) {
        std::cout << "copy" << std::endl;
    };
};

Container y;

int main() {
    // [] , [&], [=] difference
    // [] - capture no local variables
    // [=] - capture all local variables (that are used in the lambda) by copy
    // [&] - capture all local variables (that are used in the lambda) by reference
    
    // CE:
    Container x;
   // auto lam1 = []() {  x;};
    //lam1();

    // Copy constructor
    auto lam2 = [=]() {  x;};
    lam2();

    // No copy
    auto lam3 = [&]() {   x;};
    lam3();

    // [] , [=] similarity
    // [] - capture global variables by reference
    // [=] - capture global variables by reference
    // [&] - capture global variables by reference
    auto lam4 = []() { y;};
    auto lam5 = [=]() { y;};
    auto lam6 = [&]() { y;};

    //lam4();
    //lam5();
    //lam6();
    
    return 0;
}