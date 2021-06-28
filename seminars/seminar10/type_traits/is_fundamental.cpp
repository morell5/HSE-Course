#include <iostream>


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

struct NullType {};

template<typename Head, typename Tail>
struct TypeList {
    typedef Head H;
    typedef Tail T;
};

template<typename TList, typename TargetType>
struct IndexOf;

template<typename TargetType>
struct IndexOf<NullType, TargetType> {
    const static int pos = -1;
};

template<typename Tail, typename TargetType>
struct IndexOf<TypeList<TargetType, Tail>, TargetType> {
    const static int pos = 0;
};

template<typename Head, typename Tail, typename TargetType>
struct IndexOf<TypeList<Head, Tail>, TargetType> {
private:
    const static int actual = IndexOf<Tail, TargetType>::pos; 
public:
    const static int pos = (actual == -1) ? -1 : actual + 1;
};


template<typename T>
class TypeTraits {
    private:
        typedef TypeList<unsigned char, TypeList<unsigned short int, TypeList<unsigned int, TypeList<unsigned long int, NullType>>>> UnsignedInts;
        typedef TypeList<signed char, TypeList<short int, TypeList<int, TypeList<long int, NullType>>>> SignedInts;
        typedef TypeList<bool, TypeList<char, TypeList<wchar_t,  NullType>>> OtherInts;
        typedef TypeList<long double, TypeList<float, TypeList<double, NullType>>> Floats;

    public:
        const static bool isUnsignedInt = IndexOf<T, UnsignedInts>::pos >= 0;
        const static bool isSignedInt = IndexOf<T, SignedInts>::pos >= 0;
        const static bool isFloat = IndexOf<T, Floats>::pos >= 0;
        const static bool isIntegral = isUnsignedInt || isSignedInt || IndexOf<T, OtherInts>::pos >= 0;
        const static bool isArithmetic = isIntegral  || isFloat;
        const static bool isFundamental = isArithmetic  || Conversion<T, void>::same;
};
int main() {
    return 0;
}