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
    
    // 1 translation unit => just use template parameter
    template<typename Func>
    void ForEachBook(Func f) {
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