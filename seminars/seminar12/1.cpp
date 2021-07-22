#include <iostream>
#include <vector>

template<>
void foo(Widget& && x) {
    puts( "foo(T&&)" );
}

// Reference collapsing (продемонстрировать правило на cppreference)
// & & -> &
// && & -> &
// & && -> &
// && && -> &&


int main() {
    Widget w{};
    foo( w );
    return 0;      
}