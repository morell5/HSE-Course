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
        container() = default;
        container(const container& c) { std::cout << "copy"; };
        container(container&& c) { std::cout << "move"; };

};

template<typename T, typename Arg>
unique<T> make_unique( Arg&&  arg) {
    return unique<T>(new T(arg));
}

struct Test { Test(int&) {}; };

int main() {
    container c;

    // передаем в make_unique lvalue, получаем вызов copy: OK!
    unique<container> p1 = make_unique<container>(c);
    // передаем в make_unique rvalue, но получаем вызов copy: не ОК, хотим move конструктор
    unique<container> p2 = make_unique<container>(std::move(c));
}