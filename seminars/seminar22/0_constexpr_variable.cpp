#include <iostream>
#include <string>

int main() {
    
    // constexpr variable

    // 0. it must have a literal type
    // CE: std::string is not a literal type
    constexpr std::string s;
    
    // 1. it must be immediatly initialized
    
    // OK:!
    constexpr int32_t x = 0;
    
    // CE:
    constexpr int32_t y;
    y = 0;

    return 0;
}
