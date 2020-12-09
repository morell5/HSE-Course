#include "list.h"
#include <iostream>
#include <stdexcept>
 
task::list::list() {
    sz = 0;
    head = nullptr;
    tail = nullptr;
}
 
task::list::list(size_t count, const int& value): list() {
    for (size_t i = 0; i < count; i++)
        push_back(value);
}
 
task::list::~list() {
    clear();
}
 
task::list::list(const task::list& other) : list() {
    operator=(other);
}

task::list& task::list::operator=(const list& other) {
    if (this != &other) {
        clear();
        node* next_to_copy = other.head;
        //Copying each element from other list
        for (size_t i = 0; i < other.size(); i++) {
            push_back(next_to_copy->value);
            next_to_copy = next_to_copy->next_node;
        }
    }
    return *this;
}
 
int& task::list::front() {
    if (size() == 0)
        throw std::runtime_error("Trying to get front element in empty list!");
    return head->value;
}
 
const int& task::list::front() const {
    if (size() == 0)
        throw std::runtime_error("Trying to get front element in empty list!");
    return head->value;
}
 
int& task::list::back() {
    if (size() == 0)
        throw std::runtime_error("Trying to get back element in empty list!");
    return tail->value;
}
 
const int& task::list::back() const {
    if (size() == 0)
        throw std::runtime_error("Trying to get back element in empty list!");
    return tail->value;
}
 
bool task::list::empty() const {
    return sz == 0;
}
 
size_t task::list::size() const {
    return sz;
}
 
void task::list::clear() {
    while (!empty())
        pop_back();
}
 
void task::list::push_back(const int& value) {
    //Creating new node
    node* new_node = new node;
    new_node->value = value;
    new_node->next_node = nullptr;
    new_node->prev_node = nullptr;
    if (empty()) {
        //If list is empty - create new node
        head = new_node;
        tail = new_node;
    }
    else {
        //If list is not empty - putting new node in back of list
        tail->next_node = new_node;
        new_node->prev_node = tail;
        tail = new_node;
    }
    sz++;
}
 
void task::list::pop_back() {
    if (size() == 0)
        throw std::runtime_error("Trying to pop element in empty list!");
    remove_node(tail);
}
 
void task::list::push_front(const int& value) {
    //Creating new node
    node* new_node = new node;
    new_node->value = value;
    new_node->next_node = nullptr;
    new_node->prev_node = nullptr;
    if (empty()) {
        //If list is empty - create new node
        head = new_node;
        tail = new_node;
    }
    else {
        //If list is not empty - putting new node in front of list
        head->prev_node = new_node;
        new_node->next_node = head;
        head = new_node;
    }
    sz++;
}
 
void task::list::pop_front() {
    if (size() == 0)
        throw std::runtime_error("Trying to pop element in empty list!");
    remove_node(head);
}
 
void task::list::resize(size_t count) {
    //if count is smaller than size, when we reduce the size of the list
    while (size() > count)
        pop_back();
 
    //if count is bigger than sizz, when we push default nodes in the list
    while (size() < count)
        push_back(0);
}
 
void task::list::swap(list& other) {
    swap(head, other.head);
    swap(tail, other.tail);
    swap(sz, other.sz);
}
 
void task::list::remove(const int& value) {
    //!Really interesting
    //If we keep to check for equality with value - when we will delete Node with it - it will be UB
    //Due to there is some trash in memory now, so we need to remember the original value
    int val = value;
    if (!empty()) {
        node* cur_node = head;
        while (cur_node->next_node != nullptr) {
            cur_node = cur_node->next_node;
            if (cur_node->prev_node->value == val) {
                remove_node(cur_node->prev_node);
            }
        }
    }
    //Using this algorithm - we won't check tail, so we do it now
    if (!empty())
        if (tail->value == val)
            pop_back();
}
 
void task::list::unique() {
    if (!empty()) {
        node* cur_node = tail;
        while (cur_node->prev_node != nullptr) {
            cur_node = cur_node->prev_node;
            if (cur_node->next_node->value == cur_node->value) {
                remove_node(cur_node->next_node);
            }
        }
    }
}
 
void task::list::sort() {
    for (int i = 0; i < size(); i++) {
        node* cur_node = head;
        for (int j = 0; j < size() - 1; j++) {
            if (cur_node->value > cur_node->next_node->value)
                swap(cur_node->value, cur_node->next_node->value);
            cur_node = cur_node->next_node;
        }
    }
}
 
void task::list::remove_node(node* rm_node) {
    if (rm_node != head)
        rm_node->prev_node->next_node = rm_node->next_node;
    else 
        head = rm_node->next_node;
    if (rm_node != tail) 
        rm_node->next_node->prev_node = rm_node->prev_node;
    else 
        tail = rm_node->prev_node;
    delete rm_node;
    --sz;
}
 
template<typename T>
void task::list::swap(T& first, T& second) {
    T swap_el = first;
    first = second;
    second = swap_el;
}