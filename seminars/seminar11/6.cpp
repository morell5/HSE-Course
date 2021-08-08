std::vector<int> v = {1, 2 , 3 , 4 ,5};
std::vector<int> v2;
v2 = v;
v2 = std::move(v);



template<typename T>
typename std::remove_reference<T>::type&& move(T&& arg) {
    return static_cast<typename std::remove_reference<T>::type&&>(arg);
}

// Before C++11 the call of createVector is redirected to operartor=, 
// but we don't need it, because createVector is a temporary object

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

// Rvalue references T&& and new value categories "xvalue", "prvalue"
// that were introduced in C++11, solves above mentioned problem.
// We  with
// std::move function

// Summary: we use std::move to redirect the createVector call to operator=(T&&)
// std::move implementat: it's just a cast of argument type to 
// the rvalue-reference type

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


// Rule of Zero

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

// Working with raw system resources we need 
// to provide user defined move-assignment/move constructor
// special member functions, otherwise double free error may occur

// Reason: the default / implicitly generated move-assignment 
// version is equal to copy-assignment
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
    delete y.pi; // double free
    return 0;
}

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

            // alternatively we can do the following
            i = std::move(w.i);
            s  = std::move(w.s);
            std::swap(pi, w.pi);
            // but pi resources in the w.pi

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