class container {};

void bar(container&) {
    
}

void bar(container&&) {
    
}

void bar(const container&) {
    
}

void bar(const container&&) {
    
}

template<typename T>
void bar(T&&) {
    
}

template<typename T>
void bar(const T&&) {
    
}

int main() {
    container w;
    // 6 не будет выбираться т.к. const T&& rvalue  w - lvalue
    bar(w); // 3->5
}