#include "widget.h"

template<typename T, typename U>
T* Create(const U& arg, const T& param) {
    return new T(arg);
}

template<typename U>
Widget* Create(const U& arg, const Widget& param) {
    return new Widget(arg, -1);
}

int main()   {
    int* ptr = new int(1);
    Widget unnecessary_object(ptr, 1);
    Create(ptr, unnecessary_object);
    return 0;
}