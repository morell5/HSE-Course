#include <type_traits>
#include <utility>

template <typename T, T v>
struct IntegralConst {
    static constexpr T kValue = v;
};

template <bool B>
using BoolConstant = IntegralConst<bool, B>;

using TrueType = BoolConstant<true>;
using FalseType = BoolConstant<false>;

int main() {
    return 0;
}