#include <iostream>
#include <vector>

int main() {
   
    std::vector<int> v1{1, 2, 3, 4, 5};
    std::vector<int> v2{};

    v2 = std::move(v1);
    return 0;
}