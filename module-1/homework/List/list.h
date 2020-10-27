#pragma once
#include <cstddef>
#include <iostream>

    class list {

    public:

        struct element {
            int value;
            element* p; //previous - предыдущий элемент
            element* n; //next - следующий элемент
        };

        list();

        list(size_t count, const int& value = int());

        ~list();
        list& operator=(list& other);


        int& front();

        int& back();


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

        int num = 0;
        element be;//begin/end



    };