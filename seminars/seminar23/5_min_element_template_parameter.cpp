#include <iostream>
#include <cassert>

// What about to introduce the template parameter?
// And this algorithm is still overly generic

// Problem: we cannot say what can be under the Iter

template <typename Iter>
Iter MinElement(Iter first, Iter last) {
    if (first == last) {
        return first;
    }
    Iter min = first;
    while (++first != last) {
        if (*first < *min) {
            min = first;
        }
    }
    return min;
}

int main() {
    int a[] = {5, 4, -1, 1, 2};
    int* p = MinElement(a, a + 5);
    assert(p == &a[2]);
    std::cout << *(p);
    return 0;
}