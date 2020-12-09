#pragma once
#include <cstddef>
 
 
namespace task {
 
 
    class list {
 
    public:
 
        list();
        list(size_t count, const int& value = int());
 
        ~list();
        list& operator=(const list& other);
        list(const list& other);
 
 
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
 
        //Node with value in node and a link to next node
        struct node {
            //The value, which is in node
            int value;
 
            //The link to the next node
            node* next_node;
 
            //The link to the previous node
            node* prev_node;
 
        };
 
        //The size of the list
        size_t sz;
 
        //The head node
        node* head;
 
        //The tail node
        node* tail;
 
        //The method, which removes the node from the list
        void remove_node(node* rm_node);
 
        //The method to swap anything
        template <typename T>
        void swap(T& first, T& second);
    };
 
}  // namespace task
