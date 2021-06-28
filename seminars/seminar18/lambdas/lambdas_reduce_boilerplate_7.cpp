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

// Explanation:
// 1. reduce boilerplate
// 2. implementaion is same as call operator (operator())

auto plus = [value=1](int x) {return x + value;};

// $_0::operator()(int) const:                           # @"$_0::operator()(int) const"
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
// plus:
int main() {
    plus(42);
    return 0;
}