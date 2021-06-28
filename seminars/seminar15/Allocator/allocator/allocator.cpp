#include "allocator.h"

template<typename T>
SimpleAllocator<T>::SimpleAllocator() {
    arena = ::operator new(2000 * sizeof(T));
}

template<typename T>
SimpleAllocator<T>::SimpleAllocator(const SimpleAllocator& other) noexcept :
    arena(other.arena)
{
}

template<typename T>
template<typename U>
SimpleAllocator<T>::SimpleAllocator(const SimpleAllocator<U>& other) noexcept : 
    arena(other.arena)
{
}

template<typename T>
SimpleAllocator<T>::~SimpleAllocator()
{
    num_allocators--;
    if (num_allocators) {
        delete arena;
    }
}


template<typename T>
SimpleAllocator<T> SimpleAllocator<T>::select_on_container_copy_construction() const {
    return SimpleAllocator();
}

template<typename T>
T* SimpleAllocator<T>::allocate(std::size_t n) {
    return ::operator new(n * sizeof(T));
}

template<typename T>
void SimpleAllocator<T>::deallocate(void* p, std::size_t n) {
    ::operator delete(p);
}

template<typename T, typename U>
bool operator==(const SimpleAllocator<T>& lhs, const SimpleAllocator<U>& rhs) noexcept {
    return true;
}

template<typename T, typename U>
bool operator!=(const SimpleAllocator<T>& lhs, const SimpleAllocator<U>& rhs) noexcept {
    return true;
}

template<typename T>
template<typename... Args>
void SimpleAllocator<T>::construct(void* p, Args&&... args) {
    // new(p) - это new expression (конкретнее placement new expression),  
    // который вызывает new operator

    new(p) value_type(std::forward<Args>(args)...);
}

template<typename T>
void SimpleAllocator<T>::destroy(void* p) {
    ::delete(p);
}

int main() {
    return 0;
}