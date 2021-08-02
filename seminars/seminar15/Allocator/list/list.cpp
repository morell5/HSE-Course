#include "list.h"

// Special member functions
template<typename T, typename Allocator>
task::list<T, Allocator>::list() :
    head(alloc.allocate(1)),
    tail(alloc.allocate(1))
{
    alloc.construct(head);
    alloc.construct(tail);
    head->next = tail;
    tail->prev = head;
}

template<typename T, typename Allocator>
task::list<T, Allocator>::list(const task::list<T, Allocator>& other) :
    alloc(std::allocator_traits<__node_allocator>::select_on_container_copy_construction(other.alloc)),
    head(alloc.allocate(1)),
    tail(alloc.allocate(1))
{
    alloc.construct(head);
    alloc.construct(tail);
    head->next = tail;
    tail->prev = head;
    
}

template<typename T, typename Allocator>
task::list<T, Allocator>::list(const task::list<T, Allocator>& other, const Allocator& alloc) : 
    alloc(alloc),
    head(alloc.allocate(1)),
    tail(alloc.allocate(1))
{
    alloc.construct(head);
    alloc.construct(tail);
    head->next = tail;
    tail->prev = head;
}

template<typename T, typename Allocator>
task::list<T, Allocator>::list(list&& other) :
    alloc(std::move(other.alloc)),
    head(other.head),
    tail(other.tail)
{
    other.head = nullptr;
    other.tail = nullptr;
}

template<typename T, typename Allocator>
task::list<T, Allocator>::list(list&& other, const Allocator& alloc) : 
    alloc(alloc),
    head(other.head),
    tail(other.tail)
{
    other.head = nullptr;
    other.tail = nullptr;
}

template<typename T, typename Allocator>
task::list<T, Allocator>::~list() {
    alloc.destroy(head);
    alloc.deallocate(head, 1);
    alloc.destroy(tail);
    alloc.deallocate(tail, 1);
}

template<typename T, typename Allocator>
void assign(typename task::list<T, Allocator>::iterator left, typename task::list<T, Allocator>::iterator right) 
{
    for (auto it = left; it != right; it++) {
        push_back(*it);
    }
}

template<typename T, typename Allocator>
void task::list<T, Allocator>::clear() 
{
    while(!empty()) {
        pop_back();
    }
}

template<typename T, typename Allocator>
task::list<T, Allocator>& task::list<T, Allocator>::operator=(const list& other) {
    if (this == &other) {
        return *this;
    }
 
    if (std::allocator_traits<decltype(alloc)>::propagete_on_container_copy_assignment::value()) {
        if (alloc != other.alloc) {
            clear();
        }
        alloc = other.alloc;
        assign(other.begin(), other.end());
    }
    return *this;
}

template<typename T, typename Allocator>
task::list<T, Allocator>& task::list<T, Allocator>::operator=(list&& other) noexcept {
    
    clear();
    if (std::allocator_traits<decltype(alloc)>::propagete_on_container_move_assignment::value()) {
        alloc = std::move(other.alloc);
        head = other.head;
        tail = other.tail;
        other.head = nullptr;
        other.tail = nullptr;
    } else if (__node_allocator::is_always_equal::value() == std::true_type() || alloc == other.alloc()) {
        head = other.head;
        tail = other.tail;
        other.head = nullptr;
        other.tail = nullptr;
    } else {
        for (auto it = other.begin(); it != other.end(); it++) {
            push_back(std::move(*it));        
        }
    }
    
    return *this;
}

template<typename T, typename Allocator>
void task::list<T, Allocator>::push_back(const T& value) 
{
    Node* p = static_cast<Node*>(alloc.allocate(1));
    // we pass the "value" to the construct -> we call the copy constructor of a Node<T>
    alloc.construct(p, value);
    p->next = tail;
    p->prev = tail->prev;
    tail->prev->next = p;
    tail->prev = p;
    size_++;
}

template<typename T, typename Allocator>
void task::list<T, Allocator>::push_back(T&& value) 
{
    Node* p = static_cast<Node*>(alloc.allocate(1));
    // for a lvalue value we need to call copy constructor
    // for a rvalue value we need to call move constructor
    // thus we need to use std::forward
    alloc.construct(p, std::forward<T>(value));
    p->next = tail;
    p->prev = tail->prev;
    tail->prev->next = p;
    tail->prev = p;
    size_++;
}

template<typename T, typename Allocator>
template<typename... Args>
void task::list<T, Allocator>::emplace_back(Args&&... args) 
{
    Node* p = static_cast<Node*>(alloc.allocate(1));
    alloc.construct(p, std::forward<Args>(args)...);
    p->next = tail;
    p->prev = tail->prev;
    tail->prev->next = p;
    tail->prev = p;
    size_++;
}

template<typename T, typename Allocator>
void task::list<T, Allocator>::pop_back() 
{ 
    Node* p = tail->prev;
    tail->prev->next = tail;
    tail->prev = p->prev;
    alloc.destroy(p);
    alloc.deallocate(p, 1);
    size_--;
}

template<typename T, typename Allocator>
typename task::list<T, Allocator>::allocator_type task::list<T, Allocator>::get_allocator() const noexcept {
    return allocator_type(alloc);
}

// Modifiers
template<typename T, typename Allocator>
void task::list<T, Allocator>::swap(list& other) noexcept 
{   
    // we use decltype to get the type of the alloc
    if (!std::allocator_traits<decltype(alloc)>::propogate_on_container_swap::value && get_allocator() != other.get_allocator()) {
        std::exit(0);
    }

    utility::__swap_allocator(alloc, other.alloc);
    std::swap(head, other.head);
    std::swap(tail, other.tail);
}

template<typename T, typename Allocator>
typename task::list<T, Allocator>::iterator task::list<T, Allocator>::begin() noexcept {
    return iterator(head->next);
}

template<typename T, typename Allocator>
typename task::list<T, Allocator>::iterator task::list<T, Allocator>::end() noexcept {
    return iterator(tail);
}

// Capacity
template<typename T, typename Allocator>
bool task::list<T, Allocator>::empty() const noexcept {
    return size_ == 0;
}

template<typename T, typename Allocator>
typename task::list<T, Allocator>::size_type task::list<T, Allocator>::size() const noexcept {
    return size_;
}

int main() {
    task::list<int> lst;
    return 0;
}