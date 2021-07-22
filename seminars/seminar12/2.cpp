#include <iostream>
#include <vector>

namespace std {
    
template<typename T, typename Arg>
unique_ptr<T> make_unique(Arg arg) {
    return unique_ptr<T>(new T(arg));
}

}

int main() {
    std::make_unique<int>( 1 );
    std::make_unique<Widget>( w );
}