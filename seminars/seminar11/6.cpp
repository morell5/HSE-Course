std::vector<int> v = {1, 2 , 3 , 4 ,5};
std::vector<int> v2;
v2 = v;

// реализовать 
v2 = std::move(v);



template<typename T>
typename std::remove_reference<T>::type&& move(T&& arg) {
    return static_cast<typename std::remove_reference<T>::type&&>(arg);
}

// до 11 стандарта вызов createVector отправлялся в operartor=, но этого не надо т.к. createVector временный объект

#include <iostream>
#include <type_traits>

template<typename T>
typename std::remove_reference<T>::type&& move(T&& arg) {
    return static_cast<typename std::remove_reference<T>::type&&>(arg);
}


class vector {
    public:
    vector& operator=(const vector& lhs) {
        std::cout << 1;
        return *this;
    }
   
};

vector createVector() {
    return vector();
}

int main() {
    vector v1;
    vector v2;
    v2 = v1;
    v2 = createVector();

    return 0;
}

// введение T&& посзволяет перенаправить вызовы createVector в operator=
// Итог: move нужен для перенаправления присваивания
// Реализуется: приведением типа аргумента к rvalue-reference

#include <iostream>
#include <type_traits>

template<typename T>
typename std::remove_reference<T>::type&& move(T&& arg) {
    return static_cast<typename std::remove_reference<T>::type&&>(arg);
}


class vector {
    public:
    vector() = default;
    vector(const vector& ) {
        std::cout << 0;
    }
    
    vector& operator=(const vector& lhs) {
        std::cout << 1;
        return *this;
    }
    
    vector& operator=(vector&& lhs) {
        std::cout << 2;
        return *this;
    }
   
};

vector createVector() {
    return vector();
}

int main() {
    vector v1;
    vector v2;
    v2 = v1;
    v2 = createVector();
    v2 = move(v1);

    return 0;
}


// container - rule of zero

#include <iostream>
#include <memory>

class container {
    private:
        int i{0};
        std::string s{};
        std::unique_ptr<int> pi{nullptr};
    public:
        container() = default;
        container( container&& w) = default;
        container& operator=( container&& w) = default;
};  

int main() {
    container x;
    return 0;
}

// при работе с сырыми ресурсами требуется переопределять move-contructor, move-operator
// иначе double free
#include <iostream>
#include <memory>

class container {
    public:
        int i{0};
        std::string s{};
        int* pi{new int(1)};
    public:
        container() = default;
        container( container&& w) = default;
        container& operator=( container&& w) = default;
};  

int main() {
    container x;
    container y = std::move(x);
    delete x.pi;
    delete y.pi;
    return 0;
}
// 


// std::exchange с C++14
#include <iostream>
#include <memory>
#include <utility>

class container {
    public:
        int i{0};
        std::string s{};
        int* pi{new int(1)};
    public:
        container() = default;
        container( container&& w) : 
            i(w.i),
            s(std::move(w.s)),
            pi(std::exchange(w.pi, nullptr))
        {
        }
};  

int main() {
    container x;
    container y = std::move(x);
    delete x.pi;
    delete y.pi;
    return 0;
}
// 


// std::exchange с C++14
#include <iostream>
#include <memory>
#include <utility>

class container {
    public:
        int i{0};
        std::string s{};
        int* pi{new int(1)};
    public:
        container() = default;
        container& operator=(container&& w) {
            delete i;
            i = std::move(w.i);
            s  = std::move(w.s);
            pi = std::move(w.pi);
            w.pi  = nullptr
            // или можно так, но ресурсы pi будут в w.pi
            i = std::move(w.i);
            s  = std::move(w.s);
            std::swap(pi, w.pi);
            return *this;
        }
};  

int main() {
    container x;
    container y = std::move(x);
    delete x.pi;
    delete y.pi;
    return 0;
}
// 