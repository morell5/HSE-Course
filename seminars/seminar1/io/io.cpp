#include <iostream>

int main(int argc, char** argv) {
    int number;
    // output the string to the stream 
    std::cout << "Your number: ";
    // read a number from the stream
    std::cin >> number;
    // output the number to the stream
    std::cout << "Value : " << number  << std::endl;
    return 0;
}