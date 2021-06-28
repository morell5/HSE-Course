#include <iostream>
#include <memory>

class container {
    public:
    container(int i, double d, int* _p) : p(_p) {};
    container(container&& w) : p(w.p) { w.p == nullptr; std::cout << "move"; };
    container(const container& w) : p(new int(*w.p)) { std::cout << "copy"; };

    private:
    int* p;
};

template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&...args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

int main() {
    std::unique_ptr<container> uniq_ptr = make_unique<container>(1,  1.0, new int(1));
    container cont(1, 1.0, new int(1));
    std::unique_ptr<container> copied_cont = make_unique<container>(cont);
    std::unique_ptr<container> moved_cont = make_unique<container>(std::move(cont));
    return 0;
}