#pragma once
#include <cstddef>


namespace task {

struct node {
    int value;
    node* prev;
    node* next;

    node(node* p, node* n, int val);
};

class list {

public:

    list();
    list(const list& other);
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

private:

    node* first = nullptr;
    node* last = nullptr;
    size_t _size = 0;

};

}  // namespace task
