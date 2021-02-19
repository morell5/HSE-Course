#pragma once

#include "../control/control.h"

template<class T>
struct remove_extent { using type = T; };

template<class T>
struct remove_extent<T[]> { using type = T; };

template<class T, std::size_t N>
struct remove_extent<T[N]> { using type = T; };

// shared_ptr
template<typename T>
class weak_ptr;

template<typename T>
class shared_ptr {
public:
    using element_type = typename remove_extent<T>::type;

    constexpr shared_ptr() noexcept = default;
    ~shared_ptr();

    template<typename Y>
    explicit shared_ptr(Y* p);

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

    template<typename U>
    friend class weak_ptr;

private:

    element_type* value_ptr = nullptr;
    shared_weak_count* control_ptr = nullptr;
};

template<typename T>
void shared_ptr<T>::swap(shared_ptr &other) noexcept {
    std::swap(control_ptr, other.control_ptr);
    std::swap(value_ptr, other.value_ptr);
}

template<typename T>
template<typename Y>
shared_ptr<T>::shared_ptr(Y* p): value_ptr(p), control_ptr(new control_block<element_type *>(p)) {}

template<typename T>
shared_ptr<T>::~shared_ptr() {
    if (control_ptr) {
        control_ptr->release_shared();
    }
    value_ptr = nullptr;
    control_ptr = nullptr;
}

template<typename T>
template<typename Y, typename Deleter>
shared_ptr<T>::shared_ptr(Y* p, Deleter deleter) noexcept :
    value_ptr(p),
    control_ptr(new control_block<T*, Deleter>(p, deleter))
    {}

template<typename T>
shared_ptr<T>::shared_ptr(const shared_ptr& other) noexcept :
    value_ptr(other.value_ptr),
    control_ptr(other.control_ptr)
{
    control_ptr->retain_shared();
}

template<typename T>
shared_ptr<T>::shared_ptr(shared_ptr&& other) noexcept :
    value_ptr(other.value_ptr),
    control_ptr(other.control_ptr)
{
    other.control_ptr = nullptr;
    other.value_ptr = nullptr;
}

template<typename T>
shared_ptr<T>& shared_ptr<T>::operator=(const shared_ptr& rhs) noexcept {
    shared_ptr<T>(rhs).swap(*this);
    return *this;
}

template<typename T>
shared_ptr<T>& shared_ptr<T>::operator=(shared_ptr&& rhs) noexcept {
    shared_ptr<T>(std::forward<shared_ptr>(rhs)).swap(*this);
    return *this;
}

template<typename T>
T* shared_ptr<T>::get() const noexcept {
    return value_ptr;
}

template<typename T>
long shared_ptr<T>::use_count() const noexcept {
    return control_ptr == nullptr ? 0 : control_ptr->use_count();
}

template<typename T>
T& shared_ptr<T>::operator*() const noexcept {
    return *value_ptr;
}

template<typename T>
T* shared_ptr<T>::operator->() const noexcept {
    return value_ptr;
}

template<typename T>
shared_ptr<T>::operator bool() const noexcept {
    return use_count() > 0 && value_ptr != nullptr;
}

template<typename T>
typename shared_ptr<T>::element_type& shared_ptr<T>::operator[](std::ptrdiff_t idx) const {
    return *(value_ptr + idx);
}

template<typename T>
void shared_ptr<T>::reset() noexcept {
    value_ptr = nullptr;
    if (control_ptr) {
        control_ptr->release_shared();
    }
}

template<typename T>
template<typename Y>
void shared_ptr<T>::reset(Y* p) noexcept {
    shared_ptr<T>(p).swap(*this);
}

template<typename T>
template<typename Y, typename Deleter>
void shared_ptr<T>::reset(Y* p, Deleter deleter) noexcept {
    shared_ptr<T>(p, deleter).swap(*this);
}

// make_shared
template<typename T, typename... Args>
shared_ptr<T> make_shared(Args&&... args) {
    return shared_ptr<T>(new T(std::forward<Args>(args)...));
}


// shared_ptr

// weak_ptr
template<typename T>
class weak_ptr {

    using element_type = typename remove_extent<T>::type ;

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
    element_type* value_ptr = nullptr;
    shared_weak_count* control_ptr = nullptr;
};


template<typename T>
template<typename Y>
weak_ptr<T>::weak_ptr(const shared_ptr<Y>& other): value_ptr(other.value_ptr), control_ptr(other.control_ptr) {
    if (control_ptr) {
        control_ptr->retain_weak();
    }
}

template<typename T>
weak_ptr<T>::weak_ptr(const weak_ptr& other) noexcept :
    value_ptr(other.value_ptr), control_ptr(other.control_ptr)
{
    if (control_ptr) {
        control_ptr->retain_weak();
    }
}

template<typename T>
weak_ptr<T>::weak_ptr(weak_ptr&& other) noexcept :
    value_ptr(other.value_ptr),
    control_ptr(std::move(other.control_ptr))
    {
        other.value_ptr = nullptr;
        other.control_ptr = nullptr;
    }

template<typename T>
void weak_ptr<T>::reset() noexcept {
    if (control_ptr && value_ptr) {
        value_ptr = nullptr;
        control_ptr->release_weak();
        control_ptr = nullptr;
    }
}

template<typename T>
void weak_ptr<T>::swap(weak_ptr<T>& other) noexcept {
    std::swap(value_ptr, other.value_ptr);
    std::swap(control_ptr, other.control_ptr);
}

template<typename T>
bool weak_ptr<T>::expired() noexcept {
    return control_ptr == nullptr || control_ptr->use_count() <= 0;
}

template<typename T>
shared_ptr<T> weak_ptr<T>::lock() const noexcept {
    shared_ptr<T> res;
    res.control_ptr = control_ptr ? control_ptr->lock() : control_ptr;
    if (res.control_ptr) {
        res.value_ptr = this->value_ptr;
    }

    return res;
}

template<typename T>
template<typename Y>
weak_ptr<T>& weak_ptr<T>::operator=(const shared_ptr<Y>& other) {
    reset();

    this->control_ptr = other.control_ptr;
    this->value_ptr = other.value_ptr;
    if (control_ptr) {
        control_ptr->retain_weak();
    }
}

template<typename T>
weak_ptr<T>& weak_ptr<T>::operator=(const weak_ptr& other) noexcept {
    if (this == other) {
        return *this;
    }
    reset();
    this->value_ptr = other.value_ptr;
    this->control_ptr = other.control_ptr;
    if (control_ptr) {
        control_ptr->retain_weak();
    }

    return *this;
}

template<typename T>
weak_ptr<T>& weak_ptr<T>::operator=(weak_ptr&& other) noexcept {
    reset();
    this->value_ptr = other.value_ptr;
    this->control_ptr = other.control_ptr;
    other.control_ptr = nullptr;
    other.value_ptr = nullptr;

    return *this;
}
