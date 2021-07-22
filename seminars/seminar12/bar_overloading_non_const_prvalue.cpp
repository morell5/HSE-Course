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

container make_container() {
    return container();

}

int main() {
    bar(make_container());
}