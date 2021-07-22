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
        container(const container& c) : arg(c.arg) { std::cout << "hello"; };
        container(int _arg) : arg(_arg) {}

    private:
        int arg;
};

template<typename T, typename Arg>
unique<T> make_unique( Arg&&  arg) {
    return unique<T>(new T(arg));
}

struct Test { Test(int&) {}; };

int main() {
    int i = 1;
    // CE: т.к. в Test конструктор int&, а Arg const& выводится в const int &
    unique<Test> p1 = make_unique<Test>(i);
}