#include <iostream>

// Constant Expressions motivation:
// Pros:
// Similar to template metaprogramming but syntax much simpler and familiar with C++
// Easy to maintain
// No runtime cost
// errors detection at compile time

constexpr size_t Size() {return 1;}

template <size_t N>
struct Array {};

int main() {
  
    const size_t size = 1;

    // constant expressions can be used as non-type template parameters
    Array<Size()> a1;
    Array<size> a2;

    // constant expressions can be used as array sizes
   
    // OK!
    int32_t arr1[size];

    // OK!
    int32_t arr2[Size()];

    // CE
    int32_t cn = 0;
    int32_t arr3[cn];

    return 0;
}
