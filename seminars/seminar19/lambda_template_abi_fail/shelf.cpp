#include "shelf.h"

Book::Book(std::string&& _title) : title(std::move(_title)) {}

std::string Book::get_title() const { return title; }

void Book::print() const { std::cout << title; }

template<typename Func>
void Shelf::ForEachBook(Func f) {
    for (const Book& b : books_) {
        f(b);
    }
}