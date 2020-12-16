#include <iostream>
#include <string>

template<typename Tail>
void Print(Tail tail) {
    std::cout << tail;
}

template<typename Tail, typename... Head>
void Print(Tail tail, Head ... head) {
    std::cout << tail;
    Print(head...);
}

int main() {
    Print(1, 2.0, "aaaa");
    std::cout << std::endl;

    Print(2.0, "bbbb");
    std::cout << std::endl;
    return 0;
}