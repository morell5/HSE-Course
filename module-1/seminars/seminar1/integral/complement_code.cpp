#include <bitset>
#include <iostream>

int main() {
    
    unsigned short int d = 2;   
    
    // демонстрация дополненного кода
    std::cout << d << "  : " << std::bitset<18>(d).to_string() << std::endl << std::endl; 
    std::cout << "~" << d << " : " << std::bitset<18>(~d).to_string() << std::endl; 
    std::cout << "1"  << "  : " << std::bitset<18>(1).to_string() << std::endl; 

    std::cout << -d << " : " << std::bitset<18>(-d).to_string() << std::endl; 
    return 0;
}