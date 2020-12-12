#include "list.h"

task::node::node(node* p, node* n, int val) {
    prev = p;
    next = n;
    value = val;
}

task::list::list() = default;

task::list::list(const task::list &other) {
    *this = other;
}

task::list::list(size_t count, const int &value) {
    for (size_t i = 0; i < count; ++i)
        push_back(value);
}

task::list &task::list::operator=(const task::list &other) {
    if (this == &other)
        return *this;

    clear();
    for (node* e = other.first; e != nullptr; e = e->next)
        push_back(e->value);

    return *this;
}

task::list::~list() {
    clear();
}

void task::list::clear() {
    while (!empty())
        pop_back();
}

int &task::list::front() {
    return first->value;
}

const int &task::list::front() const {
    return first->value;
}

int &task::list::back() {
    return last->value;
}

const int &task::list::back() const {
    return last->value;;
}

bool task::list::empty() const {
    return first == nullptr;
}

size_t task::list::size() const {
    return _size;
}

void task::list::push_back(const int &value = int()) {
    node* elem = new node(last, nullptr, value);

    if (first == nullptr)
        first = elem;

    if (last != nullptr)
        last->next = elem;
    last = elem;

    ++_size;
}

void task::list::pop_back() {
    if (last == nullptr)
        return;

    --_size;

    if (last->prev == nullptr){
        delete last;
        first = nullptr;
        last = nullptr;
        return;
    }
    last = last->prev;
    delete last->next;
    last->next = nullptr;
}

void task::list::push_front(const int &value = int()) {
    node* elem = new node(nullptr, first, value);

    if (last == nullptr)
        last = elem;

    if (first != nullptr)
        first->prev = elem;
    first = elem;

    ++_size;
}

void task::list::pop_front() {
    if (first == nullptr)
        return;

    --_size;

    if (first->next == nullptr){
        delete first;
        last = nullptr;
        first = nullptr;
        return;
    }
    first = first->next;
    delete first->prev;
    first->prev = nullptr;
}

void task::list::resize(size_t count) {
    if (_size < count)
        for (; _size != count; push_back());
    else
        for (; _size != count; pop_back());
}

void task::list::swap(task::list &other) {
    node* temp = first;

    first = other.first;
    other.first = temp;

    last = other.last;
    other.last = temp;
}

void task::list::remove(const int &value) {
    node* next;

    for (node* start = first; start != nullptr; start = next){

        if (_size == 10)
            _size += 0;

        next = start;
        while (next != nullptr && next->value != value)
            next = next->next;

        if (next == nullptr)
            return;

        start = next;
        next = next->next;

        if (start == first)
            first = start->next;
        if (start == last)
            last = start->prev;
        if (start->next != nullptr)
            start->next->prev = start->prev;
        if (start->prev != nullptr)
            start->prev->next = start->next;

        --_size;
        delete start;
    }
}

void task::list::unique() {
    if (first == nullptr || first == last)
        return;

    node* start = first;

    while (start != nullptr) {
        node* next = start->next;
        while (next->value == start->value && next->next != nullptr){
            next = next->next;
            --_size;
            delete next->prev;
        }

        if (next->value == start->value){
            start->next = nullptr;
            --_size;
            delete next;
        } else {
            start->next = next;
            next->prev = start;
        }

        start = start->next;
    }
}

void task::list::sort() {
    size_t last_change = _size - 1;
    for (size_t i = _size - 1; i > 0 & last_change != 0; i--)
    {
        int bound = last_change;
        last_change = 0;

        node* bubble = first;
        for (size_t j = 0; j < bound; j++, bubble = bubble->next) {
            if (bubble->value > bubble->next->value)
            {
                int temp = bubble->value;
                bubble->value = bubble->next->value;
                bubble->next->value = temp;
                last_change = j;
            }
        }
    }
}
