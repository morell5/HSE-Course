#pragma once

#include <list>
#include <memory>
#include <type_traits>

namespace task {

template<typename T, typename Allocator=std::allocator<T>>
class list {

public:
    
    using value_type = T;
    // Your code goes here

    // Special member functions
    list();

    list(const list& other) {
        // Your code goes here
    }
    list(const list& other, const Allocator& alloc);
    
    list(list&& other) :  lst(std::move(other.lst));
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
    iterator begin() noexcept;
    const_iterator begin() const noexcept;

    iterator end() noexcept;
    const_iterator end() const noexcept;

    // Capacity
    bool empty() const noexcept;
    size_type size() const noexcept;
    size_type max_size() const noexcept;

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

    allocator_type get_allocator() const noexcept;

private:
    // Your code goes here
};

}