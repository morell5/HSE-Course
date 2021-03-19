#include <cstdint>

// Topic: Conditional explicit constructor
// Boost offset_ptr minimal sample
template <typename T>
class offset_ptr {
public:
    explicit offset_ptr(T* p) {
        m_ptr = reinterpret_cast<uintptr_t>(p) - reinterpret_cast<uintptr_t>(this);
    }

    T* ptr() const noexcept {
        return reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(this) + m_ptr);
    }

    // Attempt 1 

    // U* is convertible to T* implicitly
    template <typename U>
    offset_ptr(const offset_ptr<U>& rhs) : offset_ptr(rhs.ptr()) {}

    // U* is convertible to T* with a static_cast
    template <typename U>
    explicit offset_ptr(const offset_ptr<U>& rhs) : offset_ptr(static_cast<T*>(rhs.ptr())) {}
    
    // Result: CE offset_ptr is redeclared. Reason: signatures are the same
private:
    uintptr_t m_ptr;
};

int main() {
    return 0;
}
