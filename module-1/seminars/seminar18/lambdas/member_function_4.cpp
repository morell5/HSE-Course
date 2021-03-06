class Plus {
    int value;
    public:
        Plus(int v);

        int plusme(int x) const {
            return x + value;
        }
};


// main:                                   # @main
//         push    rbp
//         mov     rbp, rsp
//         sub     rsp, 16
//         mov     dword ptr [rbp - 4], 0
//         lea     rdi, [rbp - 8]
//         mov     esi, 1
//         call    Plus::Plus(int)
//         lea     rdi, [rbp - 8]
//         mov     esi, 1
//         call    Plus::plusme(int) const
//         xor     ecx, ecx
//         mov     dword ptr [rbp - 12], eax # 4-byte Spill
//         mov     eax, ecx
//         add     rsp, 16
//         pop     rbp
//         ret
// Plus::plusme(int) const:                     # @Plus::plusme(int) const
//         push    rbp
//         mov     rbp, rsp
//         mov     qword ptr [rbp - 8], rdi
//         mov     dword ptr [rbp - 12], esi
//         mov     rax, qword ptr [rbp - 8]
//         mov     ecx, dword ptr [rbp - 12]
//         add     ecx, dword ptr [rax]
//         mov     eax, ecx
//         pop     rbp
//         ret

int main() {
    // Compiler produces: Plus::plusme(int) const: 
    Plus p(1);
    p.plusme(1);
    return 0;
}