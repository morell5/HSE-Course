#include <iostream>
#include <string>

// 0. parameter type and return type must be a literal type

// CE:
constexpr std::string Foo() {return "Foo";};

// CE:
constexpr void Foo(std::string s) {};

// OK:
constexpr const char* Foo() {return "Foo";};

// CE:
constexpr void Foo(const char* s) {};

// The standard claims 1. it must not be virtual BEFORE: C++20
// Actual: GCC 9.2.0: C++11 compiles
//         Clang 9.0.0: C++11 fails
struct Foo {
    // CE:
    int32_t constexpr virtual Bar() {return 1;};
};

// 2. The class must not have virtual base class
// Actual: GCC:9.2.0 C++11 compiles
//         Clang 9.0.0: C++11 fails
struct Base {};

struct Derived : virtual Base {
    // CE:
    int32_t constexpr Bar() {return 1;};  
};

// 3. Single statement function body BEFORE: C++14

// OK!:
constexpr const char* IsEven(int32_t value) {
    return (value % 2) != 0 ? "odd" : "even";
}

// CE:
constexpr const char* IsEven(int32_t value) {
    if ((value % 2) != 0) {
        return "odd";
    } else {
        return "even";
    }
}

// 3. C++14 gives us to use multiple statements in a function body
// OK!
constexpr const char* IsEven(int32_t value) {
    if ((value % 2) != 0) {
        return "odd";
    } else {
        return "even";
    }
}

// Constructor: function requirements + 4. 
// 4. every BASE class non-static data member and every non-static data member must be initialized

// Base class non-static data member
struct Base {
    int32_t non_static_member; 
};

struct Derived : Base {
    constexpr Derived() = default;
};

void Foo() {
    // CE: Base class non-static data member must be initialized
    Derived d;
};


struct Base {
    int32_t non_static_member = 0; 
};

struct Derived : Base {
    constexpr Derived() = default;
};

void Foo() {
    // OK!:
    Derived d;
};

// Base class non-static data member

struct Derived {
    int32_t non_static_member = 0;
    constexpr Derived() = default;
};

void Foo() {
    // CE: class non-static data member must be initialized
    Derived d;
};

struct Derived {
    int32_t non_static_member = 0;
    constexpr Derived() = default;
};

void Foo() {
    // OK!:
    Derived d;
};


int main() {

    return 0;
}
