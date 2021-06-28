#include <iostream>
#include <vector>

template<bool isPolymorphic, typename T>
struct TypevsPointerSelect {
    typedef T type;
};

template<typename T>
struct TypevsPointerSelect<false, T> {
    typedef T* type;
};

template<bool isPolymorphic, typename T>
struct TypevsReferenceSelect {
    typedef T type;
};

template<typename T>
struct TypevsReferenceSelect<false, T> {
    typedef T& type;
};

template<typename T, bool isPolymorphic>
class NinftyContainer {
private:
    typedef typename TypevsPointerSelect<isPolymorphic, T>::type type1;
    typedef typename TypevsReferenceSelect<isPolymorphic, T>::type type2;
};

int main() {

    return 0;
}