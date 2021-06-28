#include <algorithm>
#include <string>
#include <vector>

class Book {
    public:
    Book(std::string&& _title) : title(std::move(_title)) {}
    std::string get_title() const { return title; }

    private:
    std::string title;
};


bool contains_title(const std::vector<Book>& v, std::string title) {
    // Explanation:  copy constructor call
    // <=> auto t = title;
    auto has_title = [t = title](const Book& b) {
        return b.get_title() == t;
    };

    return std::find_if(v.begin(), v.end(), has_title) != v.end();
}

// stack
// title -> 1
// [has_title, a $ 1_object] t -> 2

// heap
// 1: "the lliad" 
// 2: "the lliad"
int main() {
    return 0;
}