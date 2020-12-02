#pragma once
#include <cstddef>
#include <iostream>

namespace task {
    struct element {
        element *previous, *next;
        int value;
        element(const int& value = int());
        ~element();
    };

    class list {
    public:

        list();
        list(size_t count, const int& value = int());
        list(const list& other);

        ~list();
        list& operator=(const list& other);


        int& front();
        const int& front() const;

        int& back();
        const int& back() const;


        bool empty() const;
        size_t size() const;
        void clear();


        void push_back(const int& value);
        void pop_back();
        void push_front(const int& value);
        void pop_front();
        void resize(size_t count);
        void swap(list& other);


        void remove(const int& value);
        void unique();
        void sort();

        void print();
        void delete_element(element* a);
    private:
        element *beg, *end;
        size_t length;
    };

}