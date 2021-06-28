#include <iostream>

template<bool isPolymorphic, typename T, typename U>
struct Select {
    typedef T type;
};

template<typename T, typename U>
struct Select<false, T, U> {
    typedef U type;
};

template<typename T, bool isPolymorphic>
class NinftyContainer {
private:
    typedef typename Select<isPolymorphic, T, T*>::type type;
};

int main() {
    return 0;
}