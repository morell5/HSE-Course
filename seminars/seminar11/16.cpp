// Howard Hinnant: I think the most important take-away is the programmers should be leery
// of following  patterns without thought ...
class Widget {
    private:
        int i{0};
        std::string s{};
        int* pi{nullptr};
    public:
        Widget& operator=( Widget&& w) noexcept
        {
            delete pi;
            i = std::move(w.i);
            s = std::move(w.s);
            pi = std::move(w.pi);
            w.pi = nullptr;

            return *this;
        }
};  