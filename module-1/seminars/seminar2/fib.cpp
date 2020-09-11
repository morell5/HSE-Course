#include <iostream>

namespace recursive {
    int fib(int n) {
        return n <= 1 ? n : fib(n - 1) + fib(n - 2);
    }
}

namespace iterative {
    int fib(int n) {
        if (n <= 1) {
            return n;
        }

        int num[3] = {0, 1, 1};
        for( int i = 1; i < n; i++ ) {
            num[2] = num[1] + num[0];
            num[0] = num[1];
            num[1] = num[2];
        }
        return num[1];
    }
}

int main () {
   for ( int i = 0; i < 10; i++ ) {
        std::cout << recursive::fib(i) << std::endl;
        std::cout << iterative::fib(i) << std::endl;
   }

   return 0;
}