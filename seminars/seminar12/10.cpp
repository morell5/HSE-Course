#include <iostream>
#include <vector>

// Move Semantics Pitfalls
// Core Guideline F.45: Don't return T&&

namespace std {

template<typename T>
void foo(T&&) {
    using NoRef = std::remove_reference_t<T>;
    if constexpr(std::is_integral_v<NoRef> ) {

    } else {
        
    }
}

}

int main() {
  
}