#include "list.h"

#include <set>

namespace task
{

namespace {

template <typename T>
void swap(T& a, T& b)
{
    T c = a;
    a = b;
    b = c;
}

} // namespace

list::list()
{ }


list::list(const list& other)
{
    *this = other;
}

list::list(size_t count, const int& value)
{
    for (size_t i = 0; i < count; ++i)
        push_back(value);
}

list::~list()
{
    clear();
}

list& list::operator=(const list& other)
{
    if (this == &other)
        return *this;

    clear();
    for (Element* e = other._first; e != nullptr; e = e->next)
        push_back(e->value);

    return *this;
}


int& list::front()
{
    return _first->value;
}

const int& list::front() const
{
    return _first->value;
}

int& list::back()
{
    return _last->value;
}

const int& list::back() const
{
    return _last->value;
}

bool list::empty() const
{
    return _first == nullptr;
}

size_t list::size() const
{
    size_t count = 0;
    Element* e = _first;
    while (e != nullptr) {
        ++count;
        e = e->next;
    }
    return count;
}

void list::clear()
{
    while (!empty())
        pop_back();
}


void list::push_back(const int& value)
{
    Element* e = new Element;
    e->prev = _last;
    e->next = nullptr;
    e->value = value;
    if (_last != nullptr)
        _last->next = e;
    _last = e;
    if (_first == nullptr)
        _first = e;
}

void list::pop_back()
{
    if (_last == nullptr)
        return;

    Element* e = _last;
    _last = e->prev;
    if (_last != nullptr)
        _last->next = nullptr;
    else
        _first = nullptr;
    delete e;
}

void list::push_front(const int& value)
{
    Element* e = new Element;
    e->prev = nullptr;
    e->next = _first;
    e->value = value;
    if (_first != nullptr)
        _first->prev = e;
    _first = e;
    if (_last == nullptr)
        _last = e;
}

void list::pop_front()
{
    if (_first == nullptr)
        return;

    Element* e = _first;
    _first = e->next;
    if (_first != nullptr)
        _first->prev = nullptr;
    else
        _last = nullptr;
    delete e;
}

void list::resize(size_t count)
{
    size_t size = this->size();
    if (size < count)
        for (size_t i = 0; i < count - size; ++i)
            push_back(int());
    else
        for (size_t i = 0; i < size - count; ++i)
            pop_back();
}

void list::swap(list& other)
{
    task::swap(_first, other._first);
    task::swap(_last, other._last);
}

void list::remove(const int& value)
{
    Element* e = _first;

    while (e != nullptr) {
        Element* next;

        if (e->value != value) {
            next = e->next;
        } else {
            if (e->prev != nullptr)
                e->prev->next = e->next;
            if (e->next != nullptr)
                e->next->prev = e->prev;
            if (e == _first)
                _first = e->next;
            if (e == _last)
                _last = e->prev;

            next = e->next;
            delete e;
        }

        e = next;
    }
}

void list::unique()
{
    Element* e = _first;
    std::set<int> els;

    while (e != nullptr) {
        Element* next;

        if (els.find(e->value) == els.end()) {
            els.insert(e->value);
            next = e->next;
        } else {
            e->prev->next = e->next;
            if (e->next != nullptr)
                e->next->prev = e->prev;
            if (e == _first)
                _first = e->next;
            if (e == _last)
                _last = e->prev;

            next = e->next;
            delete e;
        }

        e = next;
    }
}

void list::sort()
{
    size_t size = this->size();
    for (size_t i = 0; i < size; ++i) {
        Element* e = _first;

        for (size_t j = 0; j < size - i - 1; ++j, e = e->next)
            if (e->value > e->next->value)
                task::swap(e->value, e->next->value);
    }
}

} // namespace task
