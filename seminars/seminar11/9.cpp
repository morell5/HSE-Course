// CoreGuideline C.20.

class Widget {
    private:
        int i{0};
        std::string s{};
        unique_ptr<int> pi{};
    public:
        Widget( Widget&& w) = default;
        Widget& operator=( Widget&& w) = default;
};