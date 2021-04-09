#include <iostream>
#include <functional>
#include <string>
#include <vector>

class Book {
    public:
    Book() = default;
    Book(std::string&& _title);
    std::string get_title() const;
    void print() const;

    private:
    std::string title = "Hello\n";
};

class Shelf {
    public:
    Shelf(const uint32_t num_books) : 
        books_(num_books)
    {}

    template<typename Func>
    void ForEachBook(Func f);

    private:
        std::vector<Book> books_;
};


Book::Book(std::string&& _title) : title(std::move(_title)) {}

std::string Book::get_title() const { return title; }

void Book::print() const { std::cout << title; }

template<typename Func>
void Shelf::ForEachBook(Func f) {
    for (const Book& b : books_) {
        f(b);
    }
}

int main() {
    Shelf shelf(5);
    shelf.ForEachBook([](auto&& book){book.print();});   
    return 0;
}