
struct my_struct {
    // combine static_assert with constexpr (self check)
    static constexpr char who[] = "World";
    static_assert(who[0] == 'W', "OK!");
    static constexpr const char* a = &who[1];
    static_assert(*a == 'a', "FAIL: expected 'a'");
};

int main() {
    return 0;
}
