#include <iostream>
#include <vector>
#include <memory>


int main() {
    std::unique_ptr<int> prop;
    auto lam = [p = std::move(prop)]() {};
    auto lam2 = std::move(lam);

    // CE: call to implicitly deleted copy constructor
    // auto lam3 = lam2;

    // CE
    // std::function<void()> f = std::move(lam);
    return 0;
}