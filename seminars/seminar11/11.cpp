// CoreGuideline C.20.

class Widget {
    private:
        int i{0};
        std::string s{};
        int* pi{nullptr};
    public:
        Widget( Widget&& w) : 
        i(std::move(w.i)),
        s(std::move(w.s)),
        pi(std::move(w.pi)) 
        {}
};  