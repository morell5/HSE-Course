#pragma once
#ifndef LIST_H
#define LIST_H
#include <cstddef>

namespace task {


    class list {
        struct Node {
            int cur;
            Node* next, * prev;
        };
    private:
        Node* first;
        Node* last;
        size_t length;
    public:

        list();
        list(size_t count, const int& value = int());

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

        // Your code goes here?..


    };

}  // namespace task
#endif