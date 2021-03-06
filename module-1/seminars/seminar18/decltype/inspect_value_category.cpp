#include <iostream>
#include <type_traits>

int main() {
    // 1. put identifer (id-expression) into paranthesis
    // 2. apply decltype to paranthesised id-exp
    // 3. print std::is_same
    int* p = new int(1);
    std::cout << std::is_same<decltype((*p)), int&>::value;

    return 0;
}