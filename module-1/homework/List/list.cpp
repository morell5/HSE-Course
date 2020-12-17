#include <stdexcept>
#include <vector>
#include "list.h"

// Your code goes here...
using namespace task;


list::list() {
    NIL->setPrev(NIL);
    NIL->setNext(NIL);
}

list::list(size_t count, const int &value) : list() {
    for (size_t i = 0; i < count; i++)
        push_back(value);
    size_ = count;
}

list::list(const list &other) : list() {
    Node *otherHead = other.NIL->getNext();
    for (int i = 0; i < other.size(); i++) {
        push_back(otherHead->getValue());
        otherHead = otherHead->getNext();
    }
}

list::~list() {
    Node *tmp = NIL->getNext();
    while (tmp != NIL) {
        tmp = tmp->getNext();
        delete tmp->getPrev();
    }
    delete NIL;
}

list &list::operator=(const list &other) {
    if (this != &other) {
        clear();
        Node *tmp = other.NIL->getNext();
        while (tmp != other.NIL) {
            push_back(tmp->getValue());
            tmp = tmp->getNext();
        }
    }
    return *this;
}

int &list::front() {
    if (NIL->getNext() == NIL)
        throw std::logic_error("Cannot take front from empty list!");
    return NIL->getNext()->getValueRefer();
}

const int &list::front() const {
    if (NIL->getNext() == NIL)
        throw std::logic_error("Cannot take front from empty list!");
    return NIL->getNext()->getValueRefer();
}

int &list::back() {
    if (NIL->getPrev() == NIL)
        throw std::logic_error("Cannot take front from empty list!");
    return NIL->getPrev()->getValueRefer();
}

const int &list::back() const {
    if (NIL->getPrev() == NIL)
        throw std::logic_error("Cannot take front from empty list!");
    return NIL->getPrev()->getValueRefer();
}

bool list::empty() const {
    return size_ == 0;
}

size_t list::size() const {
    return size_;
}

void list::clear() {
    while (NIL->getNext() != NIL)
        pop_back();
    size_ = 0;
}

void list::push_back(const int &value) {
    Node *last = NIL->getPrev();
    Node *newNode = new Node(value, NIL, last);

    NIL->setPrev(newNode);
    last->setNext(newNode);
    size_++;
}

void list::pop_back() {
    Node *top = NIL->getPrev();
    if (top == NIL)
        throw std::logic_error("Cannot pop from empty list!");
    remove(top);
}

void list::push_front(const int &value) {
    Node *first = NIL->getNext();
    Node *newNode = new Node(value, first, NIL);

    first->setPrev(newNode);
    NIL->setNext(newNode);
    size_++;
}

void list::pop_front() {
    Node *top = NIL->getNext();
    if (top == NIL)
        throw std::logic_error("Cannot pop from empty list!");
    remove(top);
}

void list::resize(size_t count) {
    while (size_ < count)  // if count > size
        push_back(0);
    while (size_ > count)  // if count < size
        pop_back();

    size_ = count;
}

void list::swap(list &other) {
    Node *thisNext = NIL->getNext();
    Node *thisPrev = NIL->getPrev();

    NIL->getNext()->setPrev(other.NIL);
    NIL->setNext(other.NIL->getNext());
    NIL->getPrev()->setNext(other.NIL);
    NIL->setPrev(other.NIL->getPrev());

    other.NIL->getNext()->setPrev(NIL);
    other.NIL->setNext(thisNext);
    other.NIL->getPrev()->setNext(NIL);
    other.NIL->setPrev(thisPrev);

    size_t tmp = size_;
    size_ = other.size_;
    other.size_ = tmp;
}

void list::remove(const int &value) {
    Node *tmp = NIL->getNext();
    while (tmp != NIL) {
        tmp = tmp->getNext();
        if (tmp->getPrev()->getValue() == value)
            remove(tmp->getPrev());
    }
}

void list::unique() {
    Node *tmp = NIL->getNext()->getNext();

    while (tmp->getPrev() != NIL) {
        Node *prev = tmp->getPrev();
        if (prev->getValue() == tmp->getValue())
            remove(prev);
        tmp = tmp->getNext();
    }
}

void list::sort() {
    if (size_ < 2)
        return;
    list left = list();
    list right = list(*this);
    Node *tmp = NIL->getNext();
    for (size_t i = 0; i < size_ / 2; i++) {
        left.push_back(tmp->getValue());
        tmp = tmp->getNext();
        right.pop_front();
    }
    left.sort();
    right.sort();
    list res = merge(left, right);
    *this = res;
}

void list::remove(list::Node *node) {
    Node *prev = node->getPrev();
    Node *next = node->getNext();
    prev->setNext(next);
    next->setPrev(prev);
    delete node;
    size_--;
}

list &list::merge(list &first, list &second) {
    list *result = new list();
    Node *fHead = first.NIL->getNext();
    Node *sHead = second.NIL->getNext();
    while (fHead != first.NIL || sHead != second.NIL) {
        if (sHead == second.NIL) {
            result->push_back(fHead->getValue());
            fHead = fHead->getNext();
        } else if (fHead == first.NIL) {
            result->push_back(sHead->getValue());
            sHead = sHead->getNext();
        } else if (sHead->getValue() > fHead->getValue()) {
            result->push_back(fHead->getValue());
            fHead = fHead->getNext();
        } else {
            result->push_back(sHead->getValue());
            sHead = sHead->getNext();
        }
    }
    return *result;
}
