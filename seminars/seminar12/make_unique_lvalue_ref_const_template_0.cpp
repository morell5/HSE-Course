#include <iostream>

template<typename T>
class unique {
    public:
        unique(T* _arg) : arg(_arg) {}
    
    private:
        T* arg;
};

template<typename T, typename Arg>
unique<T> make_unique(const Arg& arg) {
    // CE: Test's constructor accepts lvalue-ref to int but arg is a const lvalue-ref to Arg
    return unique<T>(new T(arg));
}

struct Test { 
    Test(int&) {};
};

int main() {
    int i = 1;
    unique<Test> p1 = make_unique<Test>(i);
}