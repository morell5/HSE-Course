#include <cstdint>
#include <iostream>
#include <thread>

class Widget {
public:

    void SyncPrinter(int32_t x) {
        this->printer(x);
    }

    void AsyncPrinter(int32_t x) {
        run_in_thread([=]() {this->printer(x);});
        std::thread::id this_id = std::this_thread::get_id();
        std::cout << "t1:" << this_id << std::endl;
    }

private:
    
    // TODO: set type for accepting lambdas
    template<typename Func>
    void run_in_thread(Func f) {
        auto t = std::thread(f);
        t.join();
    };

    void printer(int32_t x) {
        std::thread::id this_id = std::this_thread::get_id();
        std::cout << "t2:" << this_id << std::endl;
        std::cout <<  x * x << std::endl;
    }
};

int main() {
    Widget w;
    w.AsyncPrinter(10);
    return 0;
}