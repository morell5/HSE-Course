#include <iostream>

class container {};

// 1
void bar(container&) {
    std::cout << 1;
}

// 2
void bar(container&&) {
    std::cout << 2;
}

// 3
void bar(const container&) {
    std::cout << 3;
}

// 4
void bar(const container&&) {
    std::cout << 4;   
}

// 5
template<typename T>
void bar(T&&) {
    std::cout << 5;
}

// 6
template<typename T>
void bar(const T&&) {
    std::cout << 6;   
}

int main() {
    const container w;
    // 3->5
    bar(w);
}