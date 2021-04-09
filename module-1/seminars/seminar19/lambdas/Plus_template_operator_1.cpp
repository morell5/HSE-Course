class Plus {
public:
    Plus(int v) : value(v) {}

    // plus me is a tempate for stamping member functions 
    template<typename T>
    T operator()(T x) const {
        return x + value;
    }

private:
    int value;
};

int main() {
    auto plus = Plus(1);
    auto x = plus(42);
    auto y = plus(3.14);

    return 0;
}