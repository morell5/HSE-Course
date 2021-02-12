#include <atomic>
#include <cassert>
#include <iostream>
#include <memory>
#include <utility>

// auto_ptr depreceted
void seg_fault() {
    std::auto_ptr<int> w1(new int(1));
    // делегировали содержимое w2 w1
    std::auto_ptr<int> w2 = w1;
    std::cout << *w1;
}

// problem->solution
template<typename T>
void problem() {
    T* ptr = new T;
    // ...
    delete ptr;
}

template<typename T>
void solution(T) {
    class unique_ptr {
        public:

        ~unique_ptr() {
            delete p;
        }

        private:
            T* p = nullptr;
    };
}

// unique_move only
void copy_construct_error() {
    std::unique_ptr<int> u1(new int(1));
    // CE:
    // std::unique_ptr<int> u2(u1);
}

void move_construct() {
    std::unique_ptr<int> u1(new int(1));
    std::unique_ptr<int> u2(std::move(u1));
}

// std::unique_ptr<T[]> has partial specualization for arrays
// it is semantically equal for new[] expression
void unique_partial() {
    class container {};

    std::unique_ptr<container[]> u(new container[3]);
    container* raw_p = new container[3];
}

// unique_has template parameter
void deleter() {
    struct FileCloser {
        void operator()(FILE* fp) const {
            assert(fp != nullptr);
            fclose(fp);
        }
    };
    // we don't worry about descriptor releasing
    std::unique_ptr<FILE, FileCloser> u(fopen("C:\\tmp.txt","w"));
}

// Shared_ptr and simple_ref counting
void simple_ref_counting() {
    struct Widget {
        std::atomic<int> usecount_{1};
        Widget* acquire() {
            ++usecount_; 
            return this;
        }
        void release() {
            if (--usecount_ == 0) {
                delete this;
            }
        }
    };

    Widget* p = new Widget;
    Widget* q = p->acquire();
    p->release();
    q->release(); // calls delete here

    // Problem: we call acquire, release explicitly, but shared_ptr automates these process
}

// Solution: shared_ptr stores ptr to controll block. Control block increments ref_counts
void advanced_ref_counting() {
    struct control_block {
        std::size_t num_refs = 0;
    };

    struct my_shared_ptr {
        
        my_shared_ptr(int* p) : data(p) {
            control_ptr = new control_block;
        };
        my_shared_ptr(const my_shared_ptr& other) :
            data(other.data),
            control_ptr(other.control_ptr)
        {
            control_ptr->num_refs += 1;
        }

        ~my_shared_ptr() {
            control_ptr->num_refs -= 1;
            if (control_ptr->num_refs == 0) {
                delete data;
                delete control_ptr;
            }
        }
        
        int* data;
        control_block* control_ptr;
    };
    
    my_shared_ptr p1(new int(1));
    my_shared_ptr p2(p1);
    std::cout << p2.control_ptr->num_refs;
}

// Problem: raw new, delete
// make_shared, make_unique to the rescue!

void evolution_of_consciousness() {
    class Widget {};
    // Step1
    // explicit delete, explicit new
    auto* w1 = new Widget;
    delete w1;

    // Step2
    // no delete, but explicit new
    std::shared_ptr<Widget> w2(new Widget());

    // Step3
    // no delete, no explicit new
    auto w3 = std::make_shared<Widget>();

    
}

// my_make_shared
template<typename T, typename... Args>
std::shared_ptr<T> my_make_shared(Args&&... args) {
    return std::shared_ptr<T>(new T(std::forward<Args>(args)...));
}