
#include <iostream>
#include <vector>

// Let's write down our concepts
// Concepts for Iter:
// -Regular
// -ForwardIterator

template <typename Iter> 
Iter* MinElement(Iter* first, Iter* last) {
    if (first == last) {
        return first;
    }
    Iter* min = first;
    while (++first != last) {
        if (*first < *min) {
            min = first;
        }
    }
    return min;
}


int main() {
    return 0;
}