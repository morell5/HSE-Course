
#include "list.h"
#include <iostream>

using namespace task;

list::list() {
    first = nullptr;
    last = nullptr;
    length = 0;
}

list:: ~list() {
    while (first != nullptr) {
        Node* n = first->next;
        delete first;
        first = n;
    }
}

struct Node {
    int cur;
    Node* next, * prev;
};
   
list::list(size_t count, const int& value) {
        while (count > length) {
            this->push_back(value);
        }
    }
list& list::operator=(const list& other) {
    *this = other;
    return *this;
}


int& list::front() {
     return first->cur;
}
const int& list::front() const {
     return first->cur;
}

int& list::back() {
        return last->cur;
}
const int& list::back() const {
    return last->cur;
}


bool list::empty() const {
    return first == nullptr;
}
size_t list::size() const {
    return length;
}
void list::clear() {
    while (first != nullptr) {
        Node* n = first->next;
        delete first;
        first = n;
        length--;
    }
}


void list::push_back(const int& cur) {
    if (length == 0) {
        first = new Node;
        first->cur = cur;
        last = first;
    }
    else if (length == 1) {
        Node* newNode = new Node;
        newNode->cur = cur;
        last->next = newNode;
        last = newNode;
    }
    else {
        Node* newNode = new Node;
        newNode->cur = cur;
        last->next = newNode;
        newNode->prev = last;
        last = newNode;

    }
    length++;
}
void list::pop_back() {
    Node* futureLast = last->prev;
    delete last;
    last = futureLast;
    length--;
}
void list::push_front(const int& cur) {
    if (length == 0) {
        last = new Node;
        last->cur = cur;
        first = last;
    }
    else if (length == 1) {
        Node* newNode = new Node;
        newNode->cur = cur;
        newNode->next = first;
        first->prev = newNode;
        first = newNode;
    }
    else {
        Node* newNode = new Node;
        newNode->cur = cur;
        newNode->next = first;
        first->prev = newNode;
        first = newNode;
    }
    length++;

}
void list::pop_front() {
    Node* futureFirst = first->next;
    delete first;
    first = futureFirst;
    length--;

}
void list::resize(size_t count) {
    while (count > length) {
        this->push_back(0);
    }
    while (count < length) {
        this->pop_back();
    }
}
void list::swap(list& other) {
    list& a = *this, & b = other;
    Node* cfirst = b.first;
    Node* clast = b.last;
    size_t clength = b.length;
    b.first = a.first;
    b.length = a.length;
    b.last = a.last;
    a.first = cfirst;
    a.length = clength;
    a.last = clast;



}

void list::remove(const int& value) {
    Node* curNow = first;
    while (curNow != nullptr) {
        if (curNow->cur == value) {
            if (length == 1) {
                delete first;
            }
            else if (curNow == first) {
                first = first->next;
                delete first->prev;
                curNow = first;
                if (length == 2) {
                    last = first;
                }
            }
            else if (curNow == last) {
                last = last->prev;
                delete last->next;
                if (length == 2) {
                    first = last;
                }
            }
            else {
                curNow->prev->next = curNow->next;
                curNow->next->prev = curNow->prev;
                Node* oldCur = curNow;
                curNow = curNow->next;
                delete oldCur;
            }
        }
        else {
            curNow = curNow->next;
        }
    }
}
void list::unique() {
    Node* curNow = first;
    while (curNow != nullptr && curNow->next != nullptr) {
        if (curNow->cur == curNow->next->cur) {
            Node* delCur = curNow->next;
            if (delCur == last) {
                this->pop_back();
            }
            else {
                curNow->next = delCur->next;
                delCur->next = curNow;
                delete delCur;
                length--;
            }
        }
        else {
            curNow = curNow->next;
        }
    }
}
void list::sort() {
    for (size_t i = 0; i < length; i++) {
        Node* curNow = first;
        while (curNow != nullptr && curNow->next != nullptr) {
            if (curNow->cur > curNow->next->cur) {
                int& a = curNow->cur, & b = curNow->next->cur;
                a = a + b;
                b = a - b;
                a = a - b;
            }
            curNow = curNow->next;
        }
    }
}

// Your code goes here?..