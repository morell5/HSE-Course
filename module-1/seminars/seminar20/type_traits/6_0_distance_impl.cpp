#include <utility>

template<std::size_t Priority>
struct PriorityTag {};

auto DistanceImpl(It first, It last, PriorityTag<0>);

template<typename It>
auto Distance(It first, It last) {
    return DistanceImpl(first, last, PriorityTag<1>{});
}

int main() {
   
    return 0;
}
