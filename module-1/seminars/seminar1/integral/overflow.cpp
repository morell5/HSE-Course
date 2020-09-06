#include <bitset>
#include <iostream>

int main() {
    // unsigned overflow
    std::cout << "unsigned overflow: " << std::endl;
    unsigned short int c = 65535;
    unsigned short int d = 1;   
    
    std::cout << "c: " << c << std::endl;
    std::cout << "c: " << std::bitset<16>(c).to_string() << std::endl;
    std::cout << "d: " << d << std::endl;
    std::cout << "d: " << std::bitset<16>(d).to_string() << std::endl;

    // берем результат по модулю 2^16, получаем 0
    unsigned short sum = c + d;
    
    std::cout << "sum: " << sum << std::endl << std::endl;

    std::cout << "signed overflow: " << std::endl;

    //signed overflow: UB / зависит от компилятора, процессора
    unsigned short int a = 40000;
    short int b = a;
    std::cout << "a: " << a << std::endl;
    std::cout << "a: " << std::bitset<16>(a).to_string() << std::endl;
    std::cout << "b: " << b << std::endl;
    std::cout << "b: " << std::bitset<16>(b).to_string() << std::endl;
    // Вопрос: Почему b = -25536?
    // Ответ: 
    // 1. бинарное слово не изменяется
    // 2. процессор по определению воспринимает слово, как -x
    // 3. -x = ~x + 1
    // 4. их п.3 x = 25536 (перевели бинарное слово в 10)
    return 0;
}