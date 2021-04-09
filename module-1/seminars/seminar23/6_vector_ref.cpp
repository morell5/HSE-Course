
#include <iostream>
#include <vector>

int main() {
    std::vector<int32_t&> vec;

    // CE:
    // Reason: ptr to a reference; but ... this is a symptom
    // with gcc 10.1.0 you will see
    // /opt/wandbox/gcc-10.1.0/include/c++/10.1.0/bits/alloc_traits.h:416:13: error: forming pointer to reference type 'int&'
    // 416 |       using pointer = _Tp*;
    //
    // Yes, the output to the terminal is long, but if you search, you will find the line with error message  =)
    //
    // Fundamental reason:  "int32_t& IS NOT AN OBJECT"

    // What do we want?
    // We want: to see the following error message "int& IS NOT AN OBJECT"

    // How will we solve the problem?
    // Concepts to the rescue!
    // 1. Declare concept
    // 2. Put the concept to the requirements for the type when you write your container

    // Note: Concepts can't customize error messages yet, but they still will help us
    return 0;
}