#include <iostream>

// Explanation:
// 1. there is a problem, we need write difference version for each type
// 2. C++ magles the titles to linker symbols plus1(int), plus1(double)
int plus1(int x) {
    return x + 1;
}

int plus1(double x) {
    return x + 1;
}

// plus1(int):                              # @plus1(int)
//         push    rbp
//         mov     rbp, rsp
//         mov     dword ptr [rbp - 4], edi
//         mov     eax, dword ptr [rbp - 4]
//         add     eax, 1
//         pop     rbp
//         ret
// .LCPI1_0:
//         .quad   4607182418800017408     # double 1
// plus1(double):                              # @plus1(double)
//         push    rbp
//         mov     rbp, rsp
//         movsd   xmm1, qword ptr [rip + .LCPI1_0] # xmm1 = mem[0],zero
//         movsd   qword ptr [rbp - 8], xmm0
//         addsd   xmm1, qword ptr [rbp - 8]
//         cvttsd2si       eax, xmm1
//         pop     rbp
//         ret

int main() {
    
    return 0;
}