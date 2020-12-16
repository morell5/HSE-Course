#pragma once
#include <cstddef>


namespace task {


class list {

public:

    list();
    list(size_t count, const int& value = int());

    ~list();
    list(const list& other);
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

private:

        struct node {
            int value;
            node* next_node;
            node* prev_node;
        };
 
        size_t sz;
        node* head;
        node* tail;
 
        void remove_node(node* rm_node);
 
        template <typename T>
        void swap(T& first, T& second);
    };

};
