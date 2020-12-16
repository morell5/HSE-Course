#include <algorithm>
#include <iostream>

template<typename T, std::size_t Size>
class array {
public:
    typedef T value_type;
    typedef T* pointer;
    typedef T& reference;
    
    
    template<typename... U>
    array(U... elem) : arr{elem...} { }

    class iterator;

    reference operator[](int index) {
        return arr[index];
    }

    reference operator[](int index) const {
        return arr[index];
    }

    iterator begin() {
        pointer p = &arr[0];
        auto x = iterator(p); 
        return iterator(&arr[0]); 
    }

    iterator end() {
        return iterator(&arr[Size - 1]); 
    }

    class iterator {
    public: 
        using value_type = array::value_type;
        using reference = array::reference;
        using pointer = array::pointer;
        
        iterator(pointer _ptr) : ptr(_ptr) {}

        iterator(const iterator& iterator) : ptr(iterator.ptr) {}

        iterator& operator++() {
            ptr++;
            return *this;
        }

        iterator operator++(int) {
            iterator it(*this);
            ptr++;
            return it;
        }

        pointer operator->() const {
            return ptr;
        }

        reference operator*() const {
            return *ptr;
        }

        
        bool operator==(const iterator& rhs ) {
            return ptr == rhs.ptr;
        }


        bool operator!=(const iterator& rhs ) {
            return !(*this == rhs);
        }

        
        bool operator-(const iterator& rhs ) {
            return ptr - rhs.pt;
        }

    private:
        pointer ptr;
    };

    
private:
    T arr[Size];
};


int main() {
    array<int,  4> arr = {0, 1, 2};
   
    for (auto it = arr.begin(); it != arr.end(); it++) {
        std::cout << *it;
    }
    
    return 0;
}