// Howard Hinnant: I think the most important take-away is the programmers should be leery
// of following  patterns without thought ...
class Widget {
    private:
        int i{0};
        std::string s{};
        unique_ptr<int> pi{};
    public:
        Widget& operator=( Widget&& w) = default;
};  