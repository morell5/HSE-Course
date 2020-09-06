#include <bitset>
#include <iostream>

int main() {
    short int a = 100;
    short int b = 200;
    
    std::cout << "a: " << a << std::endl;
    std::cout << "a: " << std::bitset<16>(a).to_string() << std::endl  << std::endl;
    std::cout << "b: " << b << std::endl;
    std::cout << "b: " << std::bitset<16>(b).to_string() << std::endl  << std::endl;

    // not 
    std::cout << "~a: " << ~a << std::endl;
    std::cout << "~a: " << std::bitset<16>(~a).to_string() << std::endl  << std::endl;

    // and
    std::cout << "a & b: " << (a & b) << std::endl;
    std::cout << "a & b: " << std::bitset<16>(a & b).to_string() << std::endl  << std::endl;

    // or
    std::cout << "a | b: " << (a | b) << std::endl;
    std::cout << "a | b: " << std::bitset<16>(a | b).to_string() << std::endl  << std::endl;

    // xor
    std::cout << "a ^ b: " << (a ^ b) << std::endl;
    std::cout << "a ^ b: " << std::bitset<16>(a ^ b).to_string() << std::endl  << std::endl;

    // left shift
    std::cout << "a << 2: " << (a << 2) << std::endl;
    std::cout << "a << 2: " << std::bitset<16>(a << 2).to_string() << std::endl  << std::endl;

    // right shift
    std::cout << "a >> 2: " << (a >> 2) << std::endl;
    std::cout << "a >> 2: " << std::bitset<16>(a >> 2).to_string() << std::endl  << std::endl;

    return 0;
}