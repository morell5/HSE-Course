
#include <iostream>
#include <vector>

int main() {
    // A constraint is a logical expression, that says if we can use a type with a template
    // (conjunction or disjunction)

    // Also we want to compose our concepts ->  thus we need add &&
    MutableIterator = ForwardIterator<I> && OutputIterator<I>

    return 0;
}