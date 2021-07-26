#include <memory>
#include <type_traits>

template<typename T>
class SimpleAllocator {
    private:
        template<typename U> 
        struct rebind {
            using other = SimpleAllocator<U>;
        };

    public:

        using value_type = T;
        using pointer = T*;
        using reference  = T&;
        using const_pointer = const T*;
        using const_reference = const T&;
        using size_type = std::size_t;
        using pointer_difference = std::ptrdiff_t;
        using propagate_on_container_move_assignment = std::false_type;
        using propagate_on_container_copy_assignment = std::false_type;
        using propagate_on_container_swap = std::false_type;
        using is_always_equal = std::false_type;

        SimpleAllocator();
        SimpleAllocator(const SimpleAllocator& other) noexcept;
        ~SimpleAllocator();

        template<typename U>
        SimpleAllocator(const SimpleAllocator<U>& other) noexcept;
        
        SimpleAllocator select_on_container_copy_construction() const;
        
        T* allocate(std::size_t n);
        // void* allocate(std::size_t n, void* cvp);
        void deallocate(void* p, std::size_t n);
        // std::size_t max_size() const noexcept;
        template<typename... Args>
        void construct(void* p, Args&&... args);
        void destroy(void* p);

        private:
            std::size_t num_allocators = 0;
            void* arena;
};