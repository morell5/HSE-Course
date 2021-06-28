#include <iostream>
#include <cassert>
#include <memory>
#include <chrono>

// weak_ptr
void weak_ptr_break_cycles() {
    struct Son;
    struct Daughter;

    struct Mother {
        ~Mother() {
            std::cout << "Mother gone" << std::endl;
        }

        void setSon(const std::shared_ptr<Son> s) {
            mySon = s;
        }

        void setDaughter(const std::shared_ptr<Daughter> d) {
            myDaughter = d;
        }

        std::shared_ptr<const Son> mySon;
        std::weak_ptr<const Daughter> myDaughter;
    };

    struct Son {
        Son(std::shared_ptr<Mother> m) : myMother(m) {}
        ~Son() {
            std::cout << "Som gone" << std::endl;
        }

        std::shared_ptr<const Mother> myMother;
    };

    struct Daughter {
        Daughter(std::shared_ptr<Mother> m) : myMother(m) {}
        ~Daughter() {
            std::cout << "Daughter gone" << std::endl;
        }

        std::shared_ptr<const Mother> myMother;
    };

    {
        std::shared_ptr<Mother> mother = std::shared_ptr<Mother>(new Mother);
        std::shared_ptr<Son> son = std::shared_ptr<Son>(new Son(mother));
        std::shared_ptr<Daughter> daughter = std::shared_ptr<Daughter>(new Daughter(mother));

        mother->setSon(son);
        mother->setDaughter(daughter);
    }
}

void weak_ptr_lock_logic() {
    auto shared_ptr = std::make_shared<int>(2011);
    std::weak_ptr<int> weak_ptr(shared_ptr);

    if (std::shared_ptr<int> shared_from_weak = weak_ptr.lock()) {
        std::cout << "use_count_A:" << shared_from_weak.use_count() << std::endl;
    } else {
        std::cout << "Empty_A!" << std::endl;
    }

    weak_ptr.reset();
    if (std::shared_ptr<int> shared_from_weak = weak_ptr.lock()) {
        std::cout << "use_count_B:" << shared_from_weak.use_count() << std::endl;
    } else {
        std::cout << "Empty_B!" << std::endl;
    }
}

//p.19 
void perfomance() {
    auto start = std::chrono::system_clock::now();
    for (long long i = 0; i < 100000000; i++) {
        // Case1: 
        //int* tmp(new int(i));
        //delete tmp;

        // Case2:
        //std::unique_ptr<int> tmp(new int(i));
        // Case3:
        //std::unique_ptr<int> tmp = std::make_unique<int>(i);
        // Case4:
        //std::shared_ptr<int> tmp(new int(i));
        // Case5:
        std::shared_ptr<int> tmp = std::make_shared<int>(i);
    }

    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> diff = end-start;
    std::cout << diff.count();
}

// Ownership semantic part 1
class container {};

void func(container cont) {
    // 1. Independent owner of the resource
    // 2. Deletes at the end of the scope 
}

void func(container* cont) {
    // 1. Borrows resources
    // 2. The resource could BE empty
    // 3. May delete resource 
}

void func(container& cont) {
    // 1. Borrows resources
    // 2. The resource could NOT NE empty
    // 3. Can not delete the resource
}

void func(std::unique_ptr<container> cont) {
    // 1. Independent owner of the resource
    // 2. Deletes at the end of the scope 
}

void func(std::shared_ptr<container> cont) {
    // 1. Borrow resource
    // 2. The resource could BE empty
    // 3. May delete resource at the end of the scope
}

// Ownership semantic part 2
void func(std::unique_ptr<int> p) {
    // func takes ownership
}

void func(std::unique_ptr<int>& p) {
    // func may reset resource
}

void func(std::shared_ptr<int> p) {
   // func shares ownership 
}

void func(std::shared_ptr<int>& p) {
   // func may reset reource
}

void func(const std::shared_ptr<int>& p) {
   // func may retain a reference counter
}


int main() {
    perfomance();
    return 0;
}