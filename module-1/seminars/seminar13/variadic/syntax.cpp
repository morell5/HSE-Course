class container {};

template<typename... Args>
void foo(Args... args) {
}

int main() {
    foo(1, container());    
}