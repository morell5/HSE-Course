#pragma once
#ifndef LIST_H
#define LIST_H

#include <cstddef>
#include <iostream>
#include <set>

namespace task {

    class list {

    private:
        list* next;
        list* last;
        int value;
        int size_list = 0;
        int back_element;
        int front_element;

        // for sort (merge sort)
        void merge(int left_1, int right_1, int left_2, int right_2, int* arr);

        void merge_sort(int left, int right, int* arr);

        void arr_to_list(list*& element, int* arr, int index, int n);

        void copy_back(list*& element, int* arr, int& n);

        void copy_front(list*& element, int* arr, int& n);

        // find front | back elements
        int find_back_element(list*& element, int counter); // return all back

        int find_front_element(list*& element, int counter); // return all front

        // functions for destructor
        void destructor_clear_back(list*& element);

        void destructor_clear_front(list*& element);

        // push_back
        void add_back(list*& element, int value);

        // push_front
        void add_front(list*& element, int value);

        // pop_back
        void delete_back(list*& element);

        // pop_front
        void delete_front(list*& element);

        // delete elements value
        void remove_next(list*& element, const int& value);

        void remove_last(list*& element, const int& value);

        // my code
        void walk(list* element);

        void out();

        void rebuild(list*& element);

    public:
        
        // constructors
        list();

        list(size_t count, const int& value = int());

        // destructor
        ~list();

        // equals
        list& operator=(const list& other);

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
