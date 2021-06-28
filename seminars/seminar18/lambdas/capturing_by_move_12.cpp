#include <iostream>
#include <string>

void foo() {

    std::string title("hello");
    auto has_title_t = [t = std::move(title)]() {
        return true;
    };
    std::cout << "title:" << title << std::endl;
}

int main() {
    foo();
    return 0;
}