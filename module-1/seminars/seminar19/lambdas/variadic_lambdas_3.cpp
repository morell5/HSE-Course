
int main() {
    // 1. Template parameter disappeared
    // 2. auto here is an equivalent for template parameter
    
    // tuple:  
    // 1. stores arguments
    // 2. applies foo to arguments
    auto tuple = [](auto ...xs) {
        return [=](auto foo) { return foo(xs...); };
    };

    // length:
    // 1. stores arg
    // 2. call arg with another func
    auto length = [](auto xs) {
        return xs([](auto ...z) { return sizeof...(z); });
    };

    auto three = length(tuple(1, '2', "3")); 

    return 0;
}