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
unique<T> make_unique(Arg&& arg) {
    // depending on Arg std::forward<Arg>(arg) is either lvalue or xvalue
    return unique<T>(new T(std::forward<Arg>(arg)));
}

struct Test { Test(int&) {}; };

int main() {
    container c;

    unique<container> p1 = make_unique<container>(c);
    unique<container> p2 = make_unique<container>(std::move(c));
}