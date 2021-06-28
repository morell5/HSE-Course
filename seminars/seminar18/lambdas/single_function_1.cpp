
// Explanation: C lang legacy
int plus1(int x) {
    return x + 1;
}

// this is clang for x86-64 arch
// Hypothesis: Arthur used x86 djgpp
// 
// plus1(int):                              # @plus1(int)
//         push    rbp
//         mov     rbp, rsp
//         mov     dword ptr [rbp - 4], edi
//         mov     eax, dword ptr [rbp - 4]
//         add     eax, 1
//         pop     rbp
//         ret

int main() {
    return 0;
}