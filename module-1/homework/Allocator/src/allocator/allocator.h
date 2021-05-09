#include <memory>
#include <type_traits>

const size_t kAllocationSize = 16384;

template <typename T>
class CustomAllocator {
public:
    template <typename U>
    struct rebind  // NOLINT
    {
        using other = CustomAllocator<U>;
    };

    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using const_pointer = const T*;
    using const_reference = const T&;
    using size_type = std::size_t;
    using pointer_difference = std::ptrdiff_t;
    using propagate_on_container_move_assignment = std::false_type;
    using propagate_on_container_copy_assignment = std::false_type;
    using propagate_on_container_swap = std::true_type;
    using is_always_equal = std::false_type;

    CustomAllocator();
    CustomAllocator(const CustomAllocator& other) noexcept;
    ~CustomAllocator();

    template <typename U>
    explicit CustomAllocator(const CustomAllocator<U>& other) noexcept;

    void* Arena() const
    {
        return arena_;
    }

    size_type* Allocated() const
    {
        return allocated_;
    }

    size_type* AllocatorsCount() const
    {
        return allocators_count_;
    }

    T* allocate(size_t n)  // NOLINT
    {
        if (*allocated_ + n > kAllocationSize)
        {
            throw std::runtime_error("Out of memory");
        }

        *allocated_ += n;

        return static_cast<pointer>(arena_) + (*allocated_ - n);
    }

    void deallocate(T*, size_t)  // NOLINT
    {
    };

    template <typename... Args>
    void construct(pointer p, Args&&... args)  // NOLINT
    {
        new(p) value_type(std::forward<Args>(args)...);
    };

    void destroy(pointer p)  // NOLINT
    {
        p->~T();
    };

    template <typename K, typename U>
    friend bool operator==(const CustomAllocator<K>& lhs, const CustomAllocator<U>& rhs) noexcept;
    template <typename K, typename U>
    friend bool operator!=(const CustomAllocator<K>& lhs, const CustomAllocator<U>& rhs) noexcept;

private:
    void* arena_ = nullptr;
    size_type* allocated_ = nullptr;
    size_type* allocators_count_ = nullptr;
};

template <typename T>
CustomAllocator<T>::CustomAllocator()
{
    arena_ = operator new(kAllocationSize * sizeof(value_type));
    allocated_ = new size_type(0);
    allocators_count_ = new size_type(1);
}

template <typename T>
CustomAllocator<T>::CustomAllocator(const CustomAllocator& other) noexcept
    : arena_(other.arena_), allocated_(other.allocated_), allocators_count_(other.allocators_count_)
{
    ++*allocators_count_;
}

template <typename T>
CustomAllocator<T>::~CustomAllocator()
{
    --*allocators_count_;

    if (*allocators_count_ == 0)
    {
        operator delete(arena_);
        delete allocated_;
        delete allocators_count_;
    }
}

template <typename T>
template <typename U>
CustomAllocator<T>::CustomAllocator(const CustomAllocator<U>& other) noexcept
    : arena_(other.Arena()), allocated_(other.Allocated()), allocators_count_(other.AllocatorsCount())
{
    ++*allocators_count_;
}

template <typename T, typename U>
bool operator==(const CustomAllocator<T>& lhs, const CustomAllocator<U>& rhs) noexcept
{
    return lhs.arena_ == rhs.arena_;
}

template <typename T, typename U>
bool operator!=(const CustomAllocator<T>& lhs, const CustomAllocator<U>& rhs) noexcept
{
    return !(lhs == rhs);
}
