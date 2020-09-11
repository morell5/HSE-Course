#include <bitset>
#include <iostream>

int main() {
    int a = 100;
    const int num_bits_per_byte = 8;
    const int int_num_bits = sizeof(int) * num_bits_per_byte;
    
    // Способ 1
    for (short int bit_depth = int_num_bits - 1; bit_depth >= 0; bit_depth--) {
        std::cout << ((a >> bit_depth) & 1);
    }
    std::cout << std::endl;
    
    // Способ 2
    std::cout << std::bitset<int_num_bits>(a).to_string() << std::endl;
    return 0;
}