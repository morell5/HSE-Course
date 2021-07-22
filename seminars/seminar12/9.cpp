#include <iostream>
#include <vector>

// Move Semantics Pitfalls
namespace std {

template<typename... Args>
std::unique_ptr<Widget>&& create( Args&&... args) {
    return std::make_unique<Widget>(
        std::forward<Args>(args)... );
    )
}

}

int main() {
  
}