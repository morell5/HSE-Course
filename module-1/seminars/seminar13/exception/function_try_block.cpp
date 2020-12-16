#include <iostream>
#include <string>

struct class_member {
    class_member(int x) { throw 1; }
};

struct container {
    class_member cl;
    int* p = nullptr;
    
    container() try : p(new int(1)), cl(1){
    } catch (...) {
        delete p;
    }
};


void foo() try {
    std::cout << 1;
    throw 1;
} catch(...) {

} 

// no speed-up

int main() {    
    // foo();
    // container c;
    return 0;
}