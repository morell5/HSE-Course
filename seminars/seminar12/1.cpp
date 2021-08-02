#include <iostream>
#include <vector>

template<>
void foo(Widget& && x) {
    puts( "foo(T&&)" );
}

// Reference collapsing
// & & -> &
// && & -> &
// & && -> &
// && && -> &&


int main() {
    Widget w{};
    foo( w );
    return 0;      
}