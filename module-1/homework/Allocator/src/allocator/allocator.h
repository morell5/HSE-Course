#include <memory>
#include <type_traits>
#include <new>

template<typename T>
class CustomAllocator {
public:

    template<typename U>
    struct rebind {
        using other = CustomAllocator<U>;
    };

    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using pointer = T*;
    using const_pointer = const T*;
    using size_type = std::size_t;
    using pointer_difference = std::ptrdiff_t;
    using propagate_on_container_copy_assignment = std::false_type;
    using propagate_on_container_move_assignment = std::false_type;
    using propogate_on_container_swap = std::false_type;
    using is_always_equal = std::false_type;


    CustomAllocator();
    CustomAllocator(const CustomAllocator& other) noexcept;
    ~CustomAllocator();

    template<typename U>
    explicit CustomAllocator(const CustomAllocator<U>& other) noexcept;

    T* allocate(std::size_t n);
    void deallocate(T* p, std::size_t n);
    template<typename... Args>
    void construct(pointer p, Args&&... args);
    void destroy(pointer p);

    template<typename K, typename U>
    friend bool operator==(const CustomAllocator<K>& lhs, const CustomAllocator<U>& rhs) noexcept;
    template<typename K, typename U>
    friend bool operator!=(const CustomAllocator<K>& lhs, const CustomAllocator<U>& rhs) noexcept;

private:
    void* arena_;
    int* arena_offset;
    int* curr_arena_ref_count;
};

template<typename T, typename U>
bool operator==(const CustomAllocator<T>& lhs, const CustomAllocator<U>& rhs) noexcept {
    return lhs.arena_ == rhs.arena_;
}

template<typename T, typename U>
bool operator!=(const CustomAllocator<T>& lhs, const CustomAllocator<U>& rhs) noexcept {
    return !(lhs == rhs);
}

template<typename T>
CustomAllocator<T>::CustomAllocator() {
    arena_ = ::operator new(40000 * sizeof(T));
    arena_offset = new int(0);
    curr_arena_ref_count = new int(1);
}

template<typename T>
CustomAllocator<T>::CustomAllocator(const CustomAllocator& other) noexcept :
    arena_(other.arena_),
    curr_arena_ref_count(other.curr_arena_ref_count),
    arena_offset(other.arena_offset)
{
    (*curr_arena_ref_count)++;
}

template<typename T>
template<typename U>
CustomAllocator<T>::CustomAllocator(const CustomAllocator<U>& other) noexcept :
    arena_(other.arena_),
    curr_arena_ref_count(other.curr_arena_ref_count),
    arena_offset(other.arena_offset)
{
    (*curr_arena_ref_count)++;
}

template<typename T>
CustomAllocator<T>::~CustomAllocator() {
    (*curr_arena_ref_count)--;
    if (*curr_arena_ref_count == 0) {
        ::operator delete(arena_);
        delete curr_arena_ref_count;
        delete arena_offset;
    }
}

template<typename T>
T* CustomAllocator<T>::allocate(std::size_t n) {
    int offset = *arena_offset;

    *arena_offset += n;
    return static_cast<pointer>(arena_) + offset;
}

template<typename T>
void CustomAllocator<T>::deallocate(T* p, std::size_t n) {}

template<typename T>
template<typename... Args>
void CustomAllocator<T>::construct(CustomAllocator::pointer p, Args&& ... args) {
    ::new((void*)p) T(std::forward<Args>(args)...);
}

template<typename T>
void CustomAllocator<T>::destroy(CustomAllocator::pointer p) {
    p->~T();
}


