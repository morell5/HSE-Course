#pragma once

#include <memory>
#include <type_traits>

#include "../allocator/allocator.h"

namespace utility {
    //https://github.com/llvm-mirror/libcxx/blob/master/include/memory
    template<typename Allocator>
    void __swap_allocator(Allocator& lhs, Allocator& rhs) {
        __swap_allocator(lhs, rhs, std::integral_constant<bool, std::allocator_traits<Allocator>::propagate_on_container_swap::value>());
    }

    template<typename Allocator>
    void __swap_allocator(Allocator& lhs, Allocator& rhs, std::true_type) {
        std::swap(lhs, rhs);
    }

    template<typename Allocator>
    void __swap_allocator(Allocator& lhs, Allocator& rhs, std::false_type) {}
};

namespace task {

template<typename T, typename Allocator=std::allocator<T>>
class list {

private:
    class iterator;

public:
    
    using value_type = T;
    using allocator_type = Allocator;
    using size_type = std::size_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = typename std::allocator_traits<Allocator>::pointer;
    using const_pointer = typename std::allocator_traits<Allocator>::const_pointer;
    using iterator = iterator;
    using const_iterator = const iterator;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterat = std::reverse_iterator<const iterator>;

    // Special member functions
    list();
    // explicit list( const Allocator& alloc );
    // list(size_type count, const T& value, const Allocator& alloc = Allocator());
    // explicit list( size_type count, const Allocator& alloc = Allocator() );
    
    list(const list& other);
    list(const list& other, const Allocator& alloc);
    
    list(list&& other);
    list(list&& other, const Allocator& alloc);

    ~list();

    list& operator=(const list& other);
    list& operator=(list&& other) noexcept;

    // // Element access
    // reference front();
    // const reference front() const;

    // reference back();
    // const reference back() const;

    // // Iterators
    iterator begin() noexcept;
    // const_iterator begin() const noexcept;

    iterator end() noexcept;
    // const_iterator end() noexcept;

    // // Capacity
    bool empty() const noexcept;
    size_type size() const noexcept;
    // size_type max_size() const noexcept;

    // // Modifiers
    void clear();
    void swap(list& other) noexcept;

    void push_back(const T& value);
    void push_back(T&& value);

    template<typename... Args>
    void emplace_back(Args&&... args);
    void pop_back();
    // void push_front(const T& value);
    // void pop_front();
    // void resize(size_t count);

    // // Operations
    // void remove(const T& value);
    // void unique();
    // void sort();

    allocator_type get_allocator() const noexcept;

private:
    void assign(iterator left, iterator right);

private:
    struct Node {
        value_type value;
        Node* next = nullptr;
        Node* prev = nullptr;

        Node() = default;

        Node(value_type _value, Node* _next, Node* _prev) :
            value(_value),
            next(_next),
            prev(_prev)
        {}
       
    };

    class iterator {
        public:
            iterator& operator++() {
                ptr = ptr->next;
                return *this;
            }

            iterator operator++(int) {
                iterator copy(*this);
                operator++();
                return copy;
            }

            iterator& operator--() {
                ptr = ptr->prev;
                return *this;
            }

            iterator operator--(int) {
                iterator copy(*this);
                operator--();
                return copy;
            }

        private:
            Node* ptr = nullptr;
    };

private:
    typedef  typename std::allocator_traits<Allocator>::template rebind_alloc<Node> __node_allocator;

private:
    __node_allocator alloc;
    Node* head = nullptr;
    Node* tail = nullptr;
    size_type size_ = 0;
};

}