#include <algorithm>
#include <concepts>
#include <iostream>
#include <list>

// We need to implement RandomAccessContainer concept ...

// type-based specialization - we overload operations for specific types
// that have more efficient implementation strategies
template <RandomAccessContainer Cont>
void Sort(Cont& vec) {
    std::sort(vec.begin(), vec.end());
}

template <std::totally_ordered<T>>
void Sort(std::list<T>& lst) {
    std::vector<T> vec(lst.begin(), lst.end());
    std::sort(vec.begin(), vec.end());
    std::copy(vec.begin(), vec.end(), lst.begin());
}

// concept-based specialization - overload operations for concepts with more stronger requirements
// Example: BidirectionalIterator refines ForwardIterator

// We need to implement InputIterator concept...

template <InputIterator Iter>
int Distance(Iter first, Iter last) {
    int n = 0;
    while (first != last) {
        ++n;
    }
    return n;
}

// We need to implement InputIterator concept...

template <RandomAccessIterator Iter>
int Distance(Iter first, Iter last) {
    return last - first;
}

int main() {
    return 0;
}