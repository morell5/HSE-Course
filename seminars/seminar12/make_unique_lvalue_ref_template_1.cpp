#include <iostream>

template<typename T>
class unique {
    public:
        unique(T* _arg) : arg(_arg) {}
    
    private:
        T* arg;
};

class container {
    public:
        container(const container& c) : arg(c.arg) {};
        container(int _arg) : arg(_arg) {}
    
    private:
        int arg;
};

template<typename T, typename Arg>
unique<T> make_unique(Arg& arg) {
    return unique<T>(new T(arg));
}

int main() {
    container c(1);
    // OK!
    unique<container> p = make_unique<container>(c);
    // CE: 1 is a literal type => prvalue => lvalue-ref can not be binded to prvalue
    unique<int> p = make_unique<int>(1);
}