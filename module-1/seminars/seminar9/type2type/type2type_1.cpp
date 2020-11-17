#include "widget.h"

// // Type2Type
template<typename T, typename U>
T* Create(const U& arg) {
    return new T(arg);
}   

// хочется, но нельзя
// template<typename T, typename U>
// T* Create<Widget, U>(const U& arg) {
//     return new Widget(arg, -1);
// }

int main() {
    return 0;
}