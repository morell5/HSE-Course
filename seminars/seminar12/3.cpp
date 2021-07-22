#include <iostream>
#include <vector>

namespace std {
    
template<typename T, typename Arg>
unique_ptr<T> make_unique(Arg&& arg) {
    return unique_ptr<T>(new T(std::forward<Arg>(arg)));
}

}

int main() {
  
}