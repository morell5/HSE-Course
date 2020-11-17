#include <algorithm>
#include "list.h"

// Your code goes here...
task::list::node::node(int value, task::list::node *p, task::list::node *n) : value(value), prev(p), next(n) {}

task::list::node *task::list::sort_move_node(task::list::node *from, task::list::node *dest) {
    node *temp = from->next;
    if (from->prev != nullptr)
        from->prev->next = from->next;
    if (from->next != nullptr)
        from->next->prev = from->prev;

    if (dest->next != nullptr)
        dest->next->prev = from;
    from->next = dest->next;
    dest->next = from;
    from->prev = dest;
    return temp;
}

void task::list::swap(task::list::node *&first, task::list::node *&second) {
    node *temp = first;
    first = second;
    second = temp;
}

void task::list::merge_sort(task::list::node *&l, task::list::node *&r, size_t size) {
    if (size <= 1) return;
    size_t half = size / 2;
    node *m = l;
    for (size_t i = 0; i < half; ++i) {
        m = m->next;
    }
    node *l1 = l, *r1 = m->prev, *l2 = m, *r2 = r;
    merge_sort(l1, r1, half);
    merge_sort(l2, r2, size - half);
    if (l1->value > l2->value) {
        swap(l1, l2);
        swap(r1, r2);
    }
    node *now1 = l1, *now2 = l2, *end = r2->next;
    bool flag = false;
    for (size_t i = 0; i < size - 1; ++i) {
        if (now1 == r1) flag = true;
        if (now2 != end && (flag || now2->value < now1->next->value)) {
            now2 = sort_move_node(now2, now1);
        }
        now1 = now1->next;
    }
    l = l1;
    r = now1;
}

task::list::list(const task::list &other) : list() {
    node *now = other.begin;
    while (now != nullptr) {
        push_back(now->value);
        now = now->next;
    }
}

task::list::list(size_t count, const int &value) : list() {
    for (size_t i = 0; i < count; ++i) push_back(value);
}

task::list::~list() {
    node *now = begin;
    while (now != nullptr) {
        node *temp = now;
        now = now->next;
        delete temp;
    }
}

task::list &task::list::operator=(const task::list &other) {
    list temp(other);
    swap(temp);
    return *this;
}

int &task::list::front() {
    return begin->value;
}

const int &task::list::front() const {
    return begin->value;
}

int &task::list::back() {
    return end->value;
}

const int &task::list::back() const {
    return end->value;
}

bool task::list::empty() const {
    return size_ == 0;
}

size_t task::list::size() const {
    return size_;
}

void task::list::clear() {
    while (begin != nullptr) {
        node *temp = begin;
        begin = begin->next;
        delete temp;
    }
    end = nullptr;
    size_ = 0;
}

void task::list::push_back(const int &value) {
    if (size_ == 0) {
        begin = end = new node(value);
    } else {
        end->next = new node(value, end);
        end = end->next;
    }
    ++size_;
}

void task::list::pop_back() {
    if (size_ == 1) {
        clear();
    } else {
        node *temp = end->prev;
        delete end;
        end = temp;
        end->next = nullptr;
        --size_;
    }
}

void task::list::push_front(const int &value) {
    if (size_ == 0) {
        begin = end = new node(value);
    } else {
        begin->prev = new node(value, nullptr, begin);
        begin = begin->prev;
    }
    ++size_;
}

void task::list::pop_front() {
    if (size_ == 1) {
        clear();
    } else {
        node *temp = begin->next;
        delete begin;
        begin = temp;
        begin->prev = nullptr;
        --size_;
    }
}

void task::list::resize(size_t count) {
    if (count > size_) {
        for (size_t i = 0; i < count - size_; ++i) {
            push_back(0);
        }
    } else {
        for (size_t i = 0; i < size_ - count; ++i) {
            pop_back();
        }
    }
    size_ = count;
}

void task::list::swap(task::list &other) {
    std::swap(size_, other.size_);
    swap(begin, other.begin);
    swap(end, other.end);
}

void task::list::remove(int value) {
    node *del, *tmp = begin;
    while (tmp != nullptr) {
        del = tmp;
        tmp = tmp->next;
        if (del->value == value) {
            (del->prev == nullptr ? begin : del->prev->next) = del->next;
            (del->next == nullptr ? end : del->next->prev) = del->prev;
            delete del;
            --size_;
        }
    }
}

void task::list::unique() {
    for (node *temp = begin; temp != nullptr; temp = temp->next) {
        while (temp->next != nullptr && temp->next->value == temp->value) {
            node *del = temp->next;
            temp->next = del->next;
            (del->next == nullptr ? end : del->next->prev) = del->prev;
            delete del;
            --size_;
        }
    }
}

void task::list::sort() {
    if (begin == nullptr) return;
    merge_sort(begin, end, size());
}
