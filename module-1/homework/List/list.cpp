
#include "list.h"
#include <iostream>

using namespace task;
using namespace std;
#define F(x)\
cout << x << endl;

list::list() {
    first = nullptr;
    last = nullptr;
    length = 0;
}
list::list(const list& other) {
    first = nullptr;
    last = nullptr;
    length = 0;
    Node* curNow = other.first;
    while (curNow != nullptr) {
        this->push_back(curNow->cur);
        curNow = curNow->next;
    }

}

list::~list() {
   this->clear();
}

struct Node {
    int cur;
    Node* next, * prev;
};
   
list::list(size_t count, const int& value) {
    first = nullptr;
    last = nullptr;
    length = 0;
        while (count > this->length) {
            this->push_back(value);
        }
    }

list& list::operator=(const list& other) {
    if (this == &other) {
        return *this;
    }
    this->resize(other.size());
    Node* curNow1 = this->first;
    Node* curNow2 = other.first;
    while (curNow2 != nullptr) {
        curNow1->cur = curNow2->cur;
        curNow1 = curNow1->next;
        curNow2 = curNow2->next;
    }
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
        newNode->prev = first;
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
    if (length != 1) {
        Node* lastlast = last;
		last = last->prev;
		delete lastlast;
        last->next = nullptr;	
    } else {
		delete last;
        last = nullptr;
        first = nullptr;
    }
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
    if (length != 1) {
	first = first->next;
	delete first->prev;	
    first->prev = nullptr;
    } else {
	    delete first;
        first = nullptr;
        last = nullptr;
    }
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
    size_t l1 = a.size(), l2 = b.size();
    a.length = l2;
    b.length = l1;
    Node* f1 = a.first, *f2 = b.first;
    a.first = f2;
    b.first = f1;
    Node* la1 = a.last, *la2 = b.last;
    a.last = la2;
    b.last = la1;



}

void list::remove(const int& value) {
    const int delcur = value;
    Node* curNow = first;
    while (curNow != nullptr) {
        if (curNow->cur == delcur) {
            if (curNow == first) {
                curNow = curNow->next;
                pop_front();
            }
            else if (curNow == last) {
                pop_back();
                break;
            }
            else
            {
                Node* delCur = curNow;
                curNow = curNow->next;
                delCur->prev->next = curNow;
                curNow->prev = delCur->prev;
                delete delCur;
                delCur = nullptr;
                length--;
            }
        } else {
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
                delCur->next->prev = curNow;
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