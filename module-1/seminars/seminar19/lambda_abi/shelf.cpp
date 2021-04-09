#include "shelf.h"

Book::Book(std::string&& _title) : title(std::move(_title)) {}

std::string Book::get_title() const { return title; }

void Book::print() const { std::cout << title; }

void Shelf::ForEachBook(std::function<void(const Book&)> f) {
    for (const Book& b : books_) {
        f(b);
    }
}