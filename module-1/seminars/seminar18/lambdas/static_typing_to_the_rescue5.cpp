#include <cassert>

class Plus {
    int value;
    public:
        Plus(int v);

        int plusme(int x) const {
            return x + value;
        }
};

int main() {
    auto plus = Plus(1);
    // Static typing gives as the knowladge that we call plusme of the Plus object, 
    // not something other plus me object
    auto x = plus.plusme(42);
    assert(x == 43);
    return 0;
}


