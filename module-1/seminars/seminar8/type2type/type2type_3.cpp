#include "widget.h"

template<typename T>
struct Type2Type {
    typedef T value_type;
};

template<typename T, typename U>
T* Create(const U& arg, Type2Type<U>) {
    return new T(arg);
}

template<typename U>
Widget* Create(const U& arg, Type2Type<Widget>) {
    return new Widget(arg, -1);
}

int main() {
    int* ptr = new int(1);
    Create(ptr, Type2Type<Widget>());
    return 0;
}