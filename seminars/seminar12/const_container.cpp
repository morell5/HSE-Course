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
    // 5 не будет выбираться см. посмотреть ассемблерный код, инстанс темплейта отсутствует
    bar(w); // 3->5
}