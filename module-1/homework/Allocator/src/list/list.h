#pragma once

#include <memory>
#include <type_traits>

namespace task {

template<typename T, typename Allocator=std::allocator<T>>
class list {
public:
    class iterator;
public:

    using value_type = T;
    using allocator_type = Allocator;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = typename std::allocator_traits<Allocator>::pointer;
    using const_pointer = typename std::allocator_traits<Allocator>::const_pointer;
    using iterator = iterator;
    using const_iterator = const iterator;

    // Your code goes here

    // Special member functions
    list();

    list(const list& other);

    list(const list& other, const Allocator& alloc);

    list(list&& other) noexcept;
    list(list&& other, const Allocator& alloc);

    ~list();

    list& operator=(const list& other);

    list& operator=(list&& other) noexcept;

    // Element access
    reference front();
    const_reference front() const;
    reference back();
    const_reference back() const;

    // Iterators
    iterator begin() noexcept { return iterator(NIL->getNext()); }
    const_iterator begin() const noexcept { return iterator(NIL->getNext()); }

    iterator end() noexcept { return iterator(NIL); }
    const_iterator end() const noexcept { return iterator(NIL); }

    // Capacity
    bool empty() const noexcept { return size_ == 0; }
    size_type size() const noexcept { return size_; }
//    size_type max_size() const noexcept;

    // Modifiers
    void clear();
    void swap(list& other) noexcept;

    void push_back(const T& value);
    void push_back(T&& value);
    template<typename... Args>
    void emplace_back(Args&&... args);
    void pop_back();
    void push_front(const T& value);
    void push_front(T&& value);
    template<typename... Args>
    void emplace_front(Args&&... args);
    void pop_front();

    void resize(size_type count);

    // Operations
    void remove(const T& value);
    void unique();
    void sort();

    allocator_type get_allocator() const noexcept {
        return allocator_type(alloc);
    }

private:
    class Node {
    public:

        Node(): value(), next(nullptr), prev(nullptr) {}

        explicit Node(value_type value, Node* next = nullptr, Node* prev = nullptr) {
            this->value = value;
            this->next = next;
            this->prev = prev;
        }

        value_type getValue() const { return value; }

        reference getValueRef() { return value; }

        const_reference getValueRef() const { return value;}

        const Node* getPrev() const { return prev; }

        Node* getPrev() { return prev; }

        const Node* getNext() const { return next; }

        Node* getNext() { return next; }

        void setNext(Node* newNext) { this->next = newNext; }

        void setPrev(Node* newPrev) { this->prev = newPrev; }

        ~Node() {
            this->next = nullptr;
            this->prev = nullptr;
        }

    private:
        value_type value;
        Node* prev;
        Node* next;
    };
public:
    class iterator {
        friend class std::iterator_traits<iterator>;
    public:
        typedef T value_type;
        typedef iterator self_type;
        typedef std::bidirectional_iterator_tag iterator_category;
        typedef T* pointer;
        typedef T& reference;
        typedef std::ptrdiff_t difference_type;

        explicit iterator(Node* ptr): ptr(ptr) {}

        iterator& operator++() {
            ptr = ptr->getNext();
            return *this;
        }

        iterator operator++(int) {
            iterator copy(*this);
            (*this)++;
            return copy;
        }

        iterator& operator--() {
            ptr = ptr->getPrev();
            return *this;
        }

        iterator operator--(int) {
            iterator copy(*this);
            (*this)--;
            return copy;
        }

        bool operator==(const iterator& rhs) { return ptr == rhs.ptr; }
        bool operator!=(const iterator& rhs) { return ptr != rhs.ptr; }

        reference operator*() { return ptr->getValueRef(); }
        T* operator->() { return &ptr->getValueRef(); }
    private:
        Node* ptr = nullptr;
    };

private:
    typedef typename std::allocator_traits<Allocator>::template rebind_alloc<Node> node_allocator;
    typedef typename std::allocator_traits<node_allocator> node_alloc_traits;


    node_allocator alloc;

    Node* NIL;

    size_t size_ = 0;

    static list merge(const list& left, const list& right);//begin2 == end1
    static std::pair<list*, list*> bisect(const list& source);
    static list sorted(const list& source);

    void copyValues(iterator beg, iterator end);
};

}

template<typename T, typename Allocator>
task::list<T, Allocator>::list(): NIL(alloc.allocate(1)) {
    size_ = 0;
    alloc.construct(NIL);
    NIL->setNext(NIL);
    NIL->setPrev(NIL);
}

template<typename T, typename Allocator>
task::list<T, Allocator>::list(const task::list<T, Allocator>& other):
        alloc(node_alloc_traits::select_on_container_copy_construction(other.alloc)),
        NIL(alloc.allocate(1))
{
    size_ = 0;
    alloc.construct(NIL);
    NIL->setNext(NIL);
    NIL->setPrev(NIL);

    this->copyValues(other.begin(), other.end());
}

template<typename T, typename Allocator>
task::list<T, Allocator>::list(const task::list<T, Allocator>& other, const Allocator& alloc): alloc(alloc), NIL(alloc.allocate(1)) {
    alloc.construct(NIL);
    NIL->setPrev(NIL);
    NIL->setNext(NIL);
    size_ = 0;

    this->copyValues(other.begin(), other.end());
}

template<typename T, typename Allocator>
task::list<T, Allocator>::~list() {
    if (NIL == nullptr) {
        return;
    }
    Node* curr = NIL->getNext();
    while (curr && curr->getNext() != NIL) {
        Node* to_delete = curr;
        curr = curr->getNext();
        alloc.destroy(to_delete);
        alloc.deallocate(to_delete, 1);
    }
    alloc.destroy(NIL);
    alloc.deallocate(NIL, 1);
}

template<typename T, typename Allocator>
task::list<T, Allocator>& task::list<T, Allocator>::operator=(const task::list<T, Allocator>& other) {
    if (this != &other) {
        if (node_alloc_traits::propagate_on_container_copy_assignment::value) {
            if (alloc != other.alloc) {
                clear();
            }
            alloc = other.alloc;

        }
        clear();
        Node* other_head = other.NIL->getNext();
        for (int i = 0; i < other.size(); ++i) {
            this->push_back(other_head->getValue());
            other_head = other_head->getNext();
        }
        size_ = other.size();
    }
    return *this;
}

template<typename T, typename Allocator>
void task::list<T, Allocator>::copyValues(iterator beg, iterator end) {
    for (auto it = beg; it != end; it++) {
        push_back(*it);
    }
}

template<typename T, typename Allocator>
void task::list<T, Allocator>::clear() {
    while (size()) {
        pop_back();
    }
}

template<typename T, typename Allocator>
void task::list<T, Allocator>::push_back(const T& value) {
    Node* curr_last = NIL->getPrev();
    Node* begin = NIL;
    Node* new_node = static_cast<Node*>(alloc.allocate(1));
    alloc.construct(new_node, value);

    new_node->setNext(begin);
    new_node->setPrev(curr_last);
    begin->setPrev(new_node);
    curr_last->setNext(new_node);
    ++size_;
}

template<typename T, typename Allocator>
void task::list<T, Allocator>::pop_back() {
    Node* last = NIL->getPrev();
    if (last == NIL) {
        throw std::runtime_error("Pop back in empty list");
    }

    Node* prevLast = last->getPrev();
    prevLast->setNext(NIL);
    NIL->setPrev(prevLast);
    alloc.destroy(last);
    alloc.deallocate(last, 1);
    --size_;
}

template<typename T, typename Allocator>
void task::list<T, Allocator>::push_front(const T& value) {
    Node* new_node = static_cast<Node*>(alloc.allocate(1));
    alloc.construct(new_node, value);
    Node* curr_front = NIL->getNext();
    NIL->setNext(new_node);
    new_node->setPrev(NIL);

    new_node->setNext(curr_front);
    curr_front->setPrev(new_node);
    size_++;
}

template<typename T, typename Allocator>
void task::list<T, Allocator>::pop_front() {
    if (NIL->getNext() == NIL) {
        throw std::runtime_error("Pop front in empty list");
    }
    Node* curr_front = NIL->getNext();
    Node* second = curr_front->getNext();
    NIL->setNext(second);
    second->setPrev(NIL);
    alloc.destroy(curr_front);
    alloc.deallocate(curr_front, 1);
    size_--;
}

template<typename T, typename Allocator>
void task::list<T, Allocator>::resize(size_t count) {
    while (size_ > count) {
        pop_back();
    }
    while (size_ < count) {
        push_back({});
    }
    size_ = count;
}

template<typename T, typename Allocator>
void task::list<T, Allocator>::remove(const T& value) {
    Node* curr = NIL->getNext();
    std::vector<Node*> to_delete;
    while (curr != NIL) {
        if (curr->getValueRef() == value) {
            to_delete.push_back(curr);
            Node* prev = curr->getPrev();
            prev->setNext(curr->getNext());
            curr->getNext()->setPrev(prev);
            curr = curr->getNext();
            size_--;
        } else {
            curr = curr->getNext();
        }
    }
    for (auto& el : to_delete) {
        alloc.destroy(el);
        alloc.deallocate(el, 1);
    }
}

template<typename T, typename Allocator>
void task::list<T, Allocator>::unique() {
    Node* curr = NIL->getNext()->getNext();

    while (curr->getPrev() != NIL) {
        Node* prev = curr->getPrev();
        if (prev != NIL && prev->getValueRef() == curr->getValueRef()) {
            Node* next = curr->getNext();
            prev->setNext(next);
            next->setPrev(prev);
            size_--;
            Node* to_delete = curr;
            curr = curr->getNext();

            alloc.destroy(to_delete);
            alloc.deallocate(to_delete, 1);
        } else {
            curr = curr->getNext();
        }
    }
}

template<typename T, typename Allocator>
void task::list<T, Allocator>::push_back(T&& value) {
    Node* curr_last = NIL->getPrev();
    Node* begin = NIL;
    Node* new_node = static_cast<Node*>(alloc.allocate(1));
    alloc.construct(new_node, std::forward<T>(value));

    new_node->setNext(begin);
    new_node->setPrev(curr_last);
    begin->setPrev(new_node);
    curr_last->setNext(new_node);
    ++size_;
}

template<typename T, typename Allocator>
template<typename... Args>
void task::list<T, Allocator>::emplace_back(Args&& ... args) {
    Node* new_node = static_cast<Node*>(alloc.allocate(1));
    alloc.construct(new_node, std::forward<Args>(args)...);
    Node* curr_front = NIL->getNext();
    NIL->setNext(new_node);
    new_node->setPrev(NIL);

    new_node->setNext(curr_front);
    curr_front->setPrev(new_node);
    size_++;
}

template<typename T, typename Allocator>
void task::list<T, Allocator>::push_front(T&& value) {
    Node* new_node = static_cast<Node*>(alloc.allocate(1));
    alloc.construct(new_node, std::forward<T>(value));
    Node* curr_front = NIL->getNext();
    NIL->setNext(new_node);
    new_node->setPrev(NIL);

    new_node->setNext(curr_front);
    curr_front->setPrev(new_node);
    size_++;
}

template<typename T, typename Allocator>
template<typename... Args>
void task::list<T, Allocator>::emplace_front(Args&& ... args) {
    Node* new_node = static_cast<Node*>(alloc.allocate(1));
    alloc.construct(new_node, std::forward<Args>(args)...);
    Node* curr_front = NIL->getNext();
    NIL->setNext(new_node);
    new_node->setPrev(NIL);

    new_node->setNext(curr_front);
    curr_front->setPrev(new_node);
    size_++;
}

template<typename T, typename Allocator>
task::list<T, Allocator> task::list<T, Allocator>::merge(const task::list<T, Allocator>& left, const task::list<T, Allocator>& right) {
    task::list<T, Allocator> result;

    const Node* curr_left = left.NIL->getNext();
    const Node* curr_right = right.NIL->getNext();

    while (curr_left != left.NIL && curr_right != right.NIL) {
        if (curr_left->getValueRef() < curr_right->getValueRef()) {
            result.push_back(std::move(curr_left->getValueRef()));
            curr_left = curr_left->getNext();
        } else {
            result.push_back(std::move(curr_right->getValueRef()));
            curr_right = curr_right->getNext();
        }
    }

    while (curr_left != left.NIL) {
        result.push_back(std::move(curr_left->getValueRef()));
        curr_left = curr_left->getNext();
    }

    while (curr_right != right.NIL) {
        result.push_back(std::move(curr_right->getValueRef()));
        curr_right = curr_right->getNext();
    }

    return result;
}

template<typename T, typename Allocator>
std::pair<task::list<T, Allocator>*, task::list<T, Allocator>*> task::list<T, Allocator>::bisect(const task::list<T, Allocator>& source) {
    int size = source.size();
    auto* left = new task::list<T, Allocator>();
    auto* right = new task::list<T, Allocator>();

    Node* curr = source.NIL->getNext();

    for (int i = 0; i < size / 2; ++i, curr = curr->getNext()) {
        left->push_back(std::move(curr->getValueRef()));
    }

    for (int i = size / 2; i < size; ++i, curr = curr->getNext()) {
        right->push_back(std::move(curr->getValueRef()));
    }

    return {left, right};
}

template<typename T, typename Allocator>
task::list<T, Allocator> task::list<T, Allocator>::sorted(const task::list<T, Allocator>& source) {
    if (source.size() > 1) {
        auto res = task::list<T, Allocator>::bisect(source);
        return task::list<T, Allocator>::merge(task::list<T, Allocator>::sorted(*res.first), task::list<T, Allocator>::sorted(*res.second));
    }
    return source;
}

template<typename T, typename Allocator>
task::list<T, Allocator>::list(task::list<T, Allocator>&& other, const Allocator& alloc) :
    alloc(alloc),
    NIL(other.NIL)
{
    other.NIL = nullptr;
}

template<typename T, typename Allocator>
task::list<T, Allocator>::list(task::list<T, Allocator>&& other) noexcept :
    alloc(std::move(other.alloc)),
    NIL(other.NIL)
{
    other.NIL = nullptr;
}

template<typename T, typename Allocator>
task::list<T, Allocator>& task::list<T, Allocator>::operator=(task::list<T, Allocator>&& other) noexcept {
    clear();
    if (node_alloc_traits::propagate_on_container_move_assignment::value) {
        alloc = std::move(other.alloc);
        NIL = other.NIL;
        other.NIL = nullptr;
    } else if (node_alloc_traits::is_always_equal::value || alloc == other.alloc) {
        NIL = other.NIL;
        other.NIL = nullptr;
    } else  {
        for (auto it = other.begin(); it != other.end(); ++it) {
            push_back(std::move(*it));
        }
    }

    return *this;
}

template<typename T, typename Allocator>
typename task::list<T, Allocator>::reference task::list<T, Allocator>::front() {
    if (!size()) {
        throw std::runtime_error("get front in empty list");
    }

    return NIL->getNext()->getValueRef();
}

template<typename T, typename Allocator>
typename task::list<T, Allocator>::const_reference task::list<T, Allocator>::front() const {
    if (!size()) {
        throw std::runtime_error("get front in empty list");
    }

    return NIL->getNext()->getValueRef();
}

template<typename T, typename Allocator>
typename task::list<T, Allocator>::reference task::list<T, Allocator>::back() {
    if (!size()) {
        throw std::runtime_error("get back in empty list");
    }

    return NIL->getPrev()->getValueRef();
}

template<typename T, typename Allocator>
typename task::list<T, Allocator>::const_reference task::list<T, Allocator>::back() const {
    if (!size()) {
        throw std::runtime_error("get back in empty list");
    }

    return NIL->getPrev()->getValueRef();
}

template<typename T, typename Allocator>
void task::list<T, Allocator>::sort() {
    *this = sorted(*this);
}

template<typename T, typename Allocator>
void task::list<T, Allocator>::swap(task::list<T, Allocator>& other) noexcept {
    if (!node_alloc_traits::propagate_on_container_swap::value && alloc != other.alloc) {
        throw std::runtime_error("Swap with different allocators");
    }
    if (node_alloc_traits::propagate_on_container_swap::value) {
        std::swap(alloc, other.alloc);
    }
    std::swap(NIL, other.NIL);
}







