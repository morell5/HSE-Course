#include <iostream>
#include <concepts>
#include <memory>
#include <type_traits>
#include <vector>

// Constraining classes
template <typename T>
concept ObjectType = std::is_object<T>::value;
template <ObjectType T, typename Alloc = std::allocator<T>>
class Vector {

};

void VectorExmaple() {
     // OK!
    Vector<int> v1; 
    
    // CE: template constraint failure for 'template<class T, class Alloc>  requires  ObjectType<T> class Vector'
    // Vector<int&> v2;

    // CE: template constraint failure for 'template<class T, class Alloc>  requires  ObjectType<T> class Vecto
    // Vector<int&>* p;
}

// Constrainting variable templates
template <typename T>
concept FloatingPoint = std::is_floating_point_v<T>;
template <FloatingPoint T> T pi = 3.1451;

void VariableExample() {
    std::cout << pi<float> << std::endl;
    std::cout << pi<double> << std::endl;
}

// Constraining alias templates
template <ObjectType T>
using VectorAlias = std::vector<T>;

void AliasExample() {
    VectorAlias<int> v;
    
    // CE: error: template constraint failure for 'template<class T>  requires  ObjectType<T>
    // VectorAlias<int&> v;
}

template <class From, class To>
concept ConvertibleTo =
  std::is_convertible_v<From, To> &&
  requires(std::add_rvalue_reference_t<From> (&f)()) {
    static_cast<To>(f());
  };

// Constraining template members
template <ObjectType T, ObjectType U>
struct Pair {
    template <ConvertibleTo<T> X, ConvertibleTo<U> Y>
    Pair(const X& x, const Y& y) :
        first(x),
        second(y)
    {}

    T first;
    U second;
};

void TemplateMembersExample() {
    // OK!
     Pair<int, int> p1('a', 'b');
    // CE:
    Pair<int, int> p2(nullptr, 0);
}


// Non-template members
// Non-template members
template <class T>
concept Copyable =
  std::copy_constructible<T> &&
  std::movable<T> &&
  std::assignable_from<T&, T&> &&
  std::assignable_from<T&, const T&> &&
  std::assignable_from<T&, const T>;

template <ObjectType T, ObjectType U>
struct Pair {
    Pair() = default;

    Pair(const Pair& p) requires Copyable<T> && Copyable<U>
        : first(p.first), second(p.second) {};
    T first;
    U second;
};

void NonTemplateMembersExample() {
    Pair<std::unique_ptr<int>, int> p1;
    // CE:  required for the satisfaction of 'copy_constructible<T>' [with T = std::unique_ptr<int
    Pair<std::unique_ptr<int>, int> p2{p1};
}

int main() { 
    return 0;
}