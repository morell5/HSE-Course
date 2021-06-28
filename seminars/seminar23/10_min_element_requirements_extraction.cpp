
#include <iostream>
#include <vector>

// Let's write down our requirements for Iter:
// 1. return first (Move constructible)
// 2. Iter min = first (Copy constructible)
// 3. min = first (CopyAssignable)
// 4. first == last (Equality)


// 5. ++first (Incrementable)
// 6. *first < *min (Dereferencable)

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
    return 0;
}