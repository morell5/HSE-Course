class Plus {
    int value;
    public:
        Plus(int v);

        int operator() (int x) const {
            return x + value;
        }
};

// Plus::operator()(int) const:                          # @Plus::operator()(int) const
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
    auto plus = Plus(1);
    plus(42);
    return 0;
}