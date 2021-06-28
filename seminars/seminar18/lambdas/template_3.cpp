template<typetitle T>
T plus1(T x) {
    return x + 1;
}

// int plus1<int>(int):                       # @int plus1<int>(int)
//         push    rbp
//         mov     rbp, rsp
//         mov     dword ptr [rbp - 4], edi
//         mov     eax, dword ptr [rbp - 4]
//         add     eax, 1
//         pop     rbp
//         ret
// .LCPI2_0:
//         .quad   4607182418800017408     # double 1
// double plus1<double>(double):                       # @double plus1<double>(double)
//         push    rbp
//         mov     rbp, rsp
//         movsd   xmm1, qword ptr [rip + .LCPI2_0] # xmm1 = mem[0],zero
//         movsd   qword ptr [rbp - 8], xmm0
//         addsd   xmm1, qword ptr [rbp - 8]
//         movaps  xmm0, xmm1
//         pop     rbp
//         ret


int main() {
    // Compiler produces: plus1<int>
    auto x = plus1(42);
    // Compiler produces: plus1<double>
    auto y = plus1(3.14);
    return 0;
}