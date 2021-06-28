#include <iostream>
#include <vector>
#include <utility>

class Book {
    public:
    Book(std::string&& _title) : title(std::move(_title)) {}
    std::string get_title() const { return title; }

    private:
    std::string title;
};

// using 
class Shelf {
    public:
    // several translation units (if we want to a lambda from one obf file to another obj file) =>
    // use concreate type with overloaded operator(): syntax ConcreateType f
    // here we use std::function 
    void ForEachBook(std::function<void(const Book&)> f) {
        for (const Book& b : books_) {
            std::cout << f(b);
        }
    }

    private:
        std::vector<Book> books_;
};

int main() {
    Shelf shelf;
    shelf.ForEachBook([](auto&& book){book.get_title();});   
    return 0;
}