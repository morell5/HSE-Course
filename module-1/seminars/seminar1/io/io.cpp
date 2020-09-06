#include <iostream>

int main(int argc, char** argv) {
    int number;
    // выводим строку с запросом в поток 
    std::cout << "Your number: ";
    // считывает число из потока
    std::cin >> number;
    // выводим число в поток
    std::cout << "Value : " << number  << std::endl;
    return 0;
}