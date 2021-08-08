#include <iostream>
#include <vector>

std::vector<int> createVector() {
    return std::vector<int>{1, 2, 3, 4, 5};
}

std::vector<int> v = {1, 2 , 3 , 4 ,5};
std::vector<int> v2;
v2 = v;

int main() {
    // std::vector<int> _tmp_ = {1, 2, 3};
    // 0xFFFFFFF
    // stack
    // v2
    // createVector's return address
    // 
    // _tmp_ 0xFFFFFFCC
    // stack
    //
    // heap
    // 
    // 3 0x
    // 2 0x
    // 1 0x
    // heap
    // 0x0000000
    std::vector<int> v2 = {};
    v2 = createVector();
    return 0;
}