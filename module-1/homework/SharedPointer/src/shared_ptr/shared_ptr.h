#pragma once

#include "../control/control.h"

// shared_ptr
template<typename T>
class weak_ptr;

template<typename T>
class shared_ptr {
    public:
        using element_type = T;

        constexpr shared_ptr() noexcept = default;
        ~shared_ptr();
      
        template<typename Y>
        shared_ptr(Y* p);

        template<typename Y, typename Deleter>
        shared_ptr(Y* p, Deleter deleter) noexcept;
        
        shared_ptr(const shared_ptr& other) noexcept;
        shared_ptr(shared_ptr&& other) noexcept;

        shared_ptr& operator=( const shared_ptr& r ) noexcept;

        template<typename Y>
        shared_ptr& operator=( const shared_ptr<Y>& r ) noexcept;

        shared_ptr& operator=( shared_ptr&& r ) noexcept;

        template<typename Y>
        shared_ptr& operator=( shared_ptr<Y>&& r ) noexcept;
        
        // Modifiers
        void reset() noexcept;
        
        template<typename Y>
        void reset(Y* p) noexcept;
        
        template<typename Y, typename Deleter>
        void reset(Y*p, Deleter deleter) noexcept;

        void swap(shared_ptr& other) noexcept;

        // Observers
        T* get() const noexcept;
        long use_count() const noexcept;
        T& operator*() const noexcept;
        T* operator->() const noexcept;
        element_type& operator[](std::ptrdiff_t idx) const;
        explicit operator bool() const noexcept;

    private:
        // Your code goes here...
};

// make_shared

// Your code goes here...

// make_shared

// shared_ptr

// Your code goes here...

// shared_ptr

template<typename T>
class weak_ptr {
    
    using element_type = T;
    
public:

    // Special-member functions
    constexpr weak_ptr() noexcept = default;
    template<typename Y>
    weak_ptr(const shared_ptr<Y>& other);
    weak_ptr(const weak_ptr& other) noexcept;
    weak_ptr(weak_ptr&& other) noexcept;
    template<typename Y>
    weak_ptr& operator=(const shared_ptr<Y>& other);
    weak_ptr& operator=(const weak_ptr& other) noexcept;
    weak_ptr& operator=(weak_ptr&& other) noexcept;

    ~weak_ptr() = default;

    // Modifiers
    void reset() noexcept;
    void swap(weak_ptr<T>& other) noexcept;

    // Observers
    bool expired() noexcept;
    shared_ptr<T> lock() const noexcept;

    template<typename U> friend class shared_ptr;

public:
    // Your code goes here...
};


// weak_ptr

// Your code goes here...

// weak_ptr