#include <iostream>

class Base {};

class Derived : public Base {};

template<typename T, typename U>
class Conversion {
    public:
        typedef char Small;
        class Big {
            char unnnamed[2];
        };
   
        static Small Test(U);
        static Big Test(...);
        
        static T MakeT();
    
        const static bool converts = sizeof(Test(MakeT())) == sizeof(Small);
        const static bool same = false;
};

template<typename T>
class Conversion<T, T> {
    public:
        const static bool converts = true;
        const static bool same = true;
};

#define SUPERSUBCLASS(T, U) (Conversion<const U*, const T*>::converts && !Conversion<const T*, const void*>::same)

#define SUPERSUBCLASS_STRICT(T, U) (SUPERSUBCLASS(T, U) && !Conversion<const T, const U>::same)

int main() {    
    return 0;
}