#include "list.h"
#include <iostream>
#include <stdexcept>
 
task::list::list() : sz(0), head(nullptr), tail(nullptr) {
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
        for (size_t i = 0; i < other.size(); i++) {
            push_back(next_to_copy->value);
            next_to_copy = next_to_copy->next_node;
        }
    }
    return *this;
}
 
int& task::list::front() {
    if (empty())
        throw std::runtime_error("Trying to get front element in empty list!");
    return head->value;
}
 
const int& task::list::front() const {
    if (empty())
        throw std::runtime_error("Trying to get front element in empty list!");
    return head->value;
}
 
int& task::list::back() {
    if (empty())
        throw std::runtime_error("Trying to get back element in empty list!");
    return tail->value;
}
 
const int& task::list::back() const {
    if (empty())
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
    node* new_node = new node;
    new_node->value = value;
    new_node->next_node = nullptr;
    new_node->prev_node = nullptr;
    if (empty()) {
        head = new_node;
        tail = new_node;
    }
    else {
        tail->next_node = new_node;
        new_node->prev_node = tail;
        tail = new_node;
    }
    sz++;
}
 
void task::list::pop_back() {
    if (empty())
        throw std::runtime_error("Trying to pop element in empty list!");
    remove_node(tail);
}
 
void task::list::push_front(const int& value) {
    node* new_node = new node;
    new_node->value = value;
    new_node->next_node = nullptr;
    new_node->prev_node = nullptr;
    if (empty()) {
        head = new_node;
        tail = new_node;
    }
    else {
        head->prev_node = new_node;
        new_node->next_node = head;
        head = new_node;
    }
    sz++;
}
 
void task::list::pop_front() {
    if (empty())
        throw std::runtime_error("Trying to pop element in empty list!");
    remove_node(head);
}
 
void task::list::resize(size_t count) {
    while (size() > count)
        pop_back();
    while (size() < count)
        push_back(0);
}
 
void task::list::swap(list& other) {
    swap(head, other.head);
    swap(tail, other.tail);
    swap(sz, other.sz);
}
 
void task::list::remove(const int& value) {
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
    for (size_t i = 0; i < size(); i++) {
        node* cur_node = head;
        for (size_t j = 0; j < size() - 1; j++) {
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
