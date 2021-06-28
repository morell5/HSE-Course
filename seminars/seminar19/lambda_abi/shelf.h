#pragma once

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

    void ForEachBook(std::function<void(const Book&)> f);

    private:
        std::vector<Book> books_;
};