#include <cstdio>

int g = 10;
auto kitten = [=]() { return g + 1; };
auto cat = [g=g]() { return g + 1; };    

int main() {
    
    g = 20;
    printf("%d %d\t", kitten(), cat());
    // Out: 21 11
    // Explanation: cat makes a local copy g; kitten always tracks global g and make a copy just on the function call
    // expression kitten(), only on the kitten() you make a copy of g in kitten
    // in the cat lambda you make a copy of g just you reach line 5, because lambda is an object
    // and ypu intialize an object in line 5 
    return 0;
}