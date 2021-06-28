#include <iostream>
#include <vector>
#include <utility>

int32_t foo(std::vector<int32_t>& v) {return 1;}

int32_t foo(std::vector<int32_t>&& v) {return 2;}

// Before C++20
auto times = [](auto&&... args) {
    return foo(std::forward<decltype(args)>(args)...);
};

// Since C++20
auto times2 = []<typename... Ts>(Ts&&... args) {
    return (std::forward<Ts>(args)...);
}

int main() {
    
    return 0;
}