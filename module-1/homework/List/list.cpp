#include "list.h"
#include <iostream>
task::Node::Node() {
    this->value = 0;
    this->next = nullptr;
    this->prev = nullptr;
}

task::Node::Node(const int& value) {
    this->value = value;
    this->next = nullptr;
    this->prev = nullptr;
}

task::list::list() {
    this->count = 0;
    this->head = nullptr;
    this->tail = nullptr;
}

task::list::list(const list& other) {
    *this = other;
}

int& task::list::front() {
    return this->head->value;
}

const int& task::list::front() const {
    return this->head->value;
}

int& task::list::back() {
    return this->tail->value;
}

const int& task::list::back() const {
    return this->tail->value;
}

bool task::list::empty() const {
    return this->count == 0;
}

size_t task::list::size() const {
    return this->count;
}

void task::list::push_back(const int& value) {
    Node* temp = new Node(value);
    ++this->count;
    if (this->count == 1) {
        this->head = this->tail = temp;
    } else {
        this->tail->next = temp;
        temp->prev = this->tail;
        this->tail = temp;
    }
}

void task::list::pop_back() {
    if(this->empty()){
        return;
    }
    Node* temp = this->tail;

    --this->count;
    if (this->count == 0) {
        this->head = this->tail = nullptr;
        delete temp;
        return;
    }
    this->tail = this->tail->prev;
    if (this->tail) {
        this->tail->next = nullptr;
    }
    delete temp;
}

void task::list::push_front(const int& value) {
    Node* temp = new Node(value);
    ++this->count;
    if (this->count == 1) {
        this->head = this->tail = temp;
    }
    else {
        temp->next = this->head;
        this->head->prev = temp;
        this->head = temp;
    }
}

void task::list::pop_front(){
    if(this->empty()){
        return;
    }
    Node* lastHead = this->head;
    if (this->count > 1) {
        this->head = this->head->next;
        --this->count;
        this->head->prev = nullptr;
    }
    else if (this->count == 1) {
        this->head = this->tail = nullptr;
        --this->count;
    }
    delete lastHead;
}

void task::list::resize(size_t newSize) {
    if (newSize > this->count) {
        size_t difference = newSize - this->count;
        for (size_t i = 0; i < difference; ++i) {
            this->push_back(0);
        }
    }
    else {
        size_t difference = this->count - newSize;
        for (size_t i = 0; i < difference; ++i) {
            this->pop_back();
        }
    }
}

void task::list::swap(task::list& other) {
    // std::swap(this->count, other.count);
    int countTemp = this->count;
    this->count = other.count;
    other.count = countTemp;
    // std::swap(this->head, other.head);
    Node* headTemp = this->head;
    this->head = other.head;
    other.head = headTemp;
    // std::swap(this->tail, other.tail);
    Node* tailTemp = this->tail;
    this->tail = other.tail;
    other.tail = tailTemp;
}

void task::list::remove(const int& value) {
    int valueToRemove = value;
    for (Node* node = this->head; node != nullptr;) {
        if (node->value == valueToRemove) {
            Node* temp = node;
            if (node->prev) {
                node->prev->next = node->next;
            }
            if (node->next) {
                node->next->prev = node->prev;
            }
            node = node->next;
            if (temp == this->head) {
                this->head = node;
            }
            else if (temp == this->tail) {
                this->tail = this->tail->prev;
            }
            --this->count;
            if (this->count == 0) {
                this->tail = nullptr;
            }
            delete temp;
        }
        else {
            node = node->next;
        }
    }
}

task::list::list(size_t quantity, const int &value) {
    for (size_t i = 0; i < quantity; ++i) {
        this->push_back(value);
    }
}

void task::list::clear() {
    while (!this->empty()) {
        this->pop_back();
    }
}
task::list::~list() {
    this->clear();
}

task::list &task::list::operator=(const task::list &other) {
    if (this == &other) {
        return *this;
    }
    this->resize(other.size());
    for (Node* q = this->head, *p = other.head; q != nullptr; q = q->next, p = p->next) {
        q->value = p->value;
    }
    return *this;
}

void task::list::unique() {
    if (this->count > 1) {
        for (Node* node = this->head->next; node != nullptr; ) {
            Node* last = node->prev;
            if (node->value == last->value) {
                Node* temp = node;
                last->next = node->next;
                if (node->next) {
                  node->next->prev = last;
                }
                if (node == this->tail) {
                  this->tail = node->prev;
                }
                node = node->next;
                delete temp;
                --this->count;
            }
            else {
                node = node->next;
            }
        }
    }
}

void task::list::sort() {
    Node *curNode;
    for(int i = 0; i <= this->count; ++i) {
        curNode = this->head;
        Node *node = curNode;
        for(int j = 0; node->next != nullptr && j < this->count - i; ++j) {
            if(node->value > node->next->value) {
                int temp = node->value;
                node->value = node->next->value;
                node->next->value = temp;
            }
            node = node->next;
        }
    }
}