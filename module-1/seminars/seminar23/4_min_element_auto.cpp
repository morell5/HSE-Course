// You want your code more generic?
#include <iostream>
#include <cassert>

// Auto to the rescue
// This algorithm is overly general!
auto MinElement(auto first, auto last) {
    if (first == last) {
        return first;
    }
    auto min = first;
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