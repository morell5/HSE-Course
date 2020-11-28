#pragma once
#ifndef LIST_H
#define LIST_H

#include <cstddef>
#include <iostream>
#include <set>

namespace task {
    
    class node
    {
    public:
        int value;
        node* back_element;
        node* next_element;
        node();
    };
    class list { 
    private:
        node main_element;
        node *first_element;
        node *last_element;
        int size_list = 0;
        
    public:
        void out();
        // constructorr
        list();

        list(int value);

        list(size_t count, const int& value = int());
        // destructor
        ~list();

        // equals
        list& operator=(const list& other);

        list(const list& other);

        // return front element
        int& front();

        const int& front() const;

        // return back element
        int& back();

        const int& back() const;

        // check on empty
        bool empty();

        // return size
        size_t size();

        // clear list
        void clear();

        // push_back
        void push_back(const int& value);

        // pop_back
        void pop_back();

        // push_front
        void push_front(const int& value);

        // pop_front
        void pop_front();
        // resize
        void resize(size_t count);

        // swap
        void swap(list& other);

        // delete elements value
        void remove(const int& value);

        // delete unique front and back
        void unique();

        // sort
        void sort();

    };

}  // namespace task
#endif
