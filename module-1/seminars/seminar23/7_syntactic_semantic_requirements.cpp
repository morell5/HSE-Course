
#include <iostream>
#include <vector>

int main() {
    // What is a concept?
    // A named predicate expressing requirements on template arguments
    // Syntactic requirements - what operations, associated types are needed
    // Semantic requirements - behaviours are required of operations
    // Complexity requirements - perfomance requirements of operations

    // Ex. ForwardIterator: 
    // For some value i - this is semantic requirement
    // Syntactic requirement: "++i" must be correct expression
    // Semantic requirement:
    //  1. when you make ++ "i" moves to the next element
    //  2. you can dereference "i" to access an  element in the range unless 
    // it's the last element in the range

    return 0;
}