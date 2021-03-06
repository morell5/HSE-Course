#include <iostream>
#include <string>

void foo() {

    std::string title("hello");
    auto has_title_t = [&]() {
       std::cout << "lam1:" << title << std::endl;
       // Explanation: [&] - means get all needed data by reference to the scope => assignment to outer title
       // [=] - captur by const + copy => CE on assignment 
       title = "world"; 
       std::cout << "lam2:" << title << std::endl;
        return true;
    };
    has_title_t();
    std::cout << "title:" << title << std::endl;
}
int main() {
    foo();
    return 0;
}