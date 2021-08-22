#include <type_traits>

// Via functions

template<typename T, typename = decltype(dynamic_cast<void*>(std::declval<std::remove_cv_t<T>*>()))>
static std::true_type foo(int);

template<typename>
static std::false_type foo(...);

template <typename T>
struct is_polymorhic_via_functions : public decltype(foo<T>(0)) {};

// Via structs

template <typename T, typename>
struct Foo : std::false_type {};

template <typename T>
struct Foo<T, decltype(dynamic_cast<void*>(std::declval<std::remove_cv_t<T>*>()))> : std::true_type {};


template <typename T>
// Foo<T, void*> well-formed -> true
// Foo<T, void*> ill-formed -> false 
struct is_polymorhic_via_structs : Foo<T, void*> {};


void remove_cv_t_explanation() {
    // we use remove_cv_t to handle cast error from const T* / volatile T* to void*
  
    struct Foo {
    public:
        virtual void foo() {};
    };

    
    using T = const Foo;
    using U = int;
    // Example: CE
    using M = decltype(dynamic_cast<void*>(std::declval<T*>()));
};

int main() {
    
    return 0;
}