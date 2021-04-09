#include <utility>

int main() {
    using T = int&;
    using U = int;

    decltype(void( std::declval<T>() = std::declval<U>() ));
    decltype( std::declval<T>() = std::declval<U>(), void());
    std::void_t<decltype( std::declval<T>() = std::declval<U>() )>;

    return 0;
}