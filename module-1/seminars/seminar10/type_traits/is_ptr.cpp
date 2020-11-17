#include <iostream>

struct NullType {};

template<typename T>
class TypeTraits {
    private:
        template<typename U> 
        struct PointerTraits {
            const static bool isPtr = false;
            typedef NullType PtrType;
        };

        template<typename U>
        struct PointerTraits<U*> {
            const static bool isPtr = true;
            typedef U* PtrType;
        };

    public:
        const static bool isPtr = PointerTraits<T>::isPtr;
        typedef typename PointerTraits<T>::PtrType PtrType; 
};

int main() {
    return 0;
}