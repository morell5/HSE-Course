#include "widget.h"

// Type2Type
template<typename T, typename U>
T* Create(const U& arg) {
    return new T(arg);
}   

// We want to customize Widget in this way, but 
// functions cannot be partially specialized  
//
// template<typename T, typename U>
// T* Create<Widget, U>(const U& arg) {
//     return new Widget(arg, -1);
// }

int main() {
    return 0;
}