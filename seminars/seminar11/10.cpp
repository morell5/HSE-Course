// CoreGuideline C.20.

class Widget {
    private:
        int i{0};
        std::string s{};
        int* pi{nullptr};
    public:
        Widget( Widget&& w) : 
        i(w.i),
        s(w.s) 
        {}
};  