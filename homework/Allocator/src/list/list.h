#pragma once

#include <list>
#include <memory>
#include <type_traits>

namespace task {

template <typename T, typename Allocator = std::allocator<T>>
class List {

public:
    using value_type = T;
    // Your code goes here

    // Special member functions
    List(){};

    List(const List& other) {
        // Your code goes here
    }
    List(const List& other, const Allocator& alloc);

    List(List&& other);
    List(List&& other, const Allocator& alloc);

    ~List();

    List& operator=(const List& other);

    List& operator=(List&& other) noexcept;

    // Element access
    reference Front();
    const_reference Front() const;
    reference Back();
    const_reference Back() const;

    // Iterators
    iterator Begin() noexcept;
    const_iterator Begin() const noexcept;

    iterator End() noexcept;
    const_iterator End() const noexcept;

    // Capacity
    bool Empty() const noexcept;

    size_type Size() const noexcept;
    size_type MaxSize() const noexcept;

    // Modifiers
    void Clear();
    void Swap(List& other) noexcept;

    void PushBack(const T& value);
    void PushBack(T&& value);
    
    template <typename... Args>
    void EmplaceBack(Args&&... args);
    void PopBack();
    void PushFront(const T& value);
    void PushFront(T&& value);
    template <typename... Args>
    void EmplaceFront(Args&&... args);
    void PopFront();

    void Resize(size_type count);

    // Operations
    void Remove(const T& value);
    void Unique();
    void Sort();

    allocator_type GetAllocator() const noexcept;

private:
    // Your code goes here
};

}  // namespace task