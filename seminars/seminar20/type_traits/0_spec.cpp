#include <iostream>

template<class T1, class T2, int32_t I>
struct A { // #0 primary template
    constexpr static int32_t val = 0;
};            
 
template<class T1, class T2, int32_t I>
struct A<T1, T2*, I> { // #4:
    constexpr static int32_t val = 4;
};   

template<class T1, int32_t I>
struct A<T1, T1*, I> { // #1:
    constexpr static int32_t val = 1;
};  

template<class T1>
struct A<int32_t, T1*, 5> { // #3: 
    constexpr static int32_t val = 3;
}; 

template<class T1, class T2, int32_t I>
struct A<T1*, T2, I> { // #2: 
    constexpr static int32_t val = 2;
}; 
 
//  Expected: partial order
//  branch0: #2 \subset #0
//  barnch1: #3 \subset #1  \subset  #4 \subset #0

int main() {

    // Selection algorithm
    // 0. Branch 0 analysis
    //    0. check #2 fail on first parameter T1*: reason first is int32_t
    // 1. Branch 1 analysis
    //    0. check #3: fail on third parameter 5: reason third parameter is 1
    //    1. check #1: success: reason T1=int32_t, T1*=int32_t*, I=1 -> choose #1

    std::cout << A<int32_t, int32_t*, 1>::val << std::endl;  // uses partial specialization #1 (T=int32_t, I=1)

    // Selection algorithm
    // 0. Branch 0 analysis
    //    0. check #2 fail on first parameter T1*: reason first is int32_t
    // 1. Branch 1 analysis
    //    0. check #3: success: reason T1=char -> spec accepts <int32_t, char*, 5> -> choose #3

    std::cout << A<int32_t, char*, 5>::val << std::endl; // uses partial specialization #3, (T=char)

    // Selection algorithm
    // 0. Branch 0 analysis
    //    0. check #2 fail on first parameter T1*: reason first is int32_t
    // 1. Branch 1 analysis
    //    0. check #3: fail on third parameter 5: reason third parameter is 1
    //    1. check #1: fail on  second parameter char*: reason T1=int32_t-> spec accepts <int32_t, int32_t*, 1>
    //    2. check #4: success: reason T1=int32_t, T2=char, I=1 -> spec accepts <int32_t, char*, 1> -> choose #4

    std::cout << A<int32_t, char*, 1>::val << std::endl; // uses partial specialization #4, (X=int32_t, T=char, I=1)

    // Selection algorithm
    // 0. Branch 0 analysis
    //    0. check #2: fail on: T1*=int32_t**
    // 1. Branch 1 analysis
    //    0. check #3: fail on third parameter 5
    //    1. check #1: fail on T1*=int32_t**
    //    2. check #4: fail on T2*=int32_t**
    //    3. choose primary template

    std::cout << A<int32_t, int32_t, 1>::val << std::endl;   // primary template

    
    
     // Selection algorithm
    // 0. Branch 0 analysis
    //    0. check #1: success: reason T1=int32_t, T1*=int32_t*, I=1 -> choose #1
    // 1. Branch 1 analysis
    //    0. check #3: fail on third parameter 5: reason third parameter is 1
    //    1. check #1: fail on T1*=int32_t**
    //    2. check #4: success: reason T1=int32_t, T2*=int32_t**, I=2 -> choose #1

    // CE: branch 0 succeeded, branch 1 succeeded
   // std::cout << A<int32_t*, int32_t*, 2>::val << std::endl;
                        
    return 0;
}