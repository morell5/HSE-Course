#include <memory>
#include <type_traits>

template<typename T>
class CustomAllocator {
    public:

        using value_type = T;
        // Your code goes here

        CustomAllocator();
        CustomAllocator(const CustomAllocator& other) noexcept;
        ~CustomAllocator();

        template<typename U>
        CustomAllocator(const CustomAllocator<U>& other) noexcept;
                
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
        // Your code goes here
};

template<typename T, typename U>
bool operator==(const CustomAllocator<T>& lhs, const CustomAllocator<U>& rhs) noexcept {
    // Your code goes here
}

template<typename T, typename U>
bool operator!=(const CustomAllocator<T>& lhs, const CustomAllocator<U>& rhs) noexcept {
    // Your code goes here
}