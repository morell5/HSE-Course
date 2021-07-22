#include <iostream>
#include <vector>

// Move Semantics Pitfalls
namespace std {

class A {
public:
    template<typename T>
    A( T&& t ) {
        : b_( std::forward<T>( t )),
        c_( std::forward<T>( t ))
    }
    {}
private:
    B b_;
    C c_;
};

}

int main() {
  
}