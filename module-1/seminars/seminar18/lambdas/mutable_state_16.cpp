#include <iostream>

int main() {
    // Explanation: we want to have a unique i for each object
    // lets declare lambda's member in square bracket. We get a CE, the reason is 
    // captye by copy -> data member read only 
    auto lam = [i=0]() { return ++i; };
    // stack
    // [c1, a $_o obj] i(0)
    // [c2, a $_o obj] i(0)

    // CE: Increment read-only
    // CE: cannot assign to a varible captured by copy in a non-mutable lambda

    // Correct
    auto lam = [i=0]() mutable { return ++i; };

    return 0;
}