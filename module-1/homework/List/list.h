#pragma once
#include <cstddef>
#include <iostream>
namespace task {

    class list {

        public:

            struct element {
                int value = 0;
                element* p; //previous 
                element* n; //next 
            };
            int num = 0;
            element be;//begin/end

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
            

    };
}
