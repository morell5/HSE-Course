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
    // Explanation: equavalent to auto& t = title;
    // be careful: if title is a local <=> on the stack -> returning the has_title you get a dangling reference t
    // (title is destroyed, t refs to title )
    auto has_title = [&t = title](const Book& b) {
        return b.get_title() == t;
    };

    return std::find_if(v.begin(), v.end(), has_title) != v.end();
}   

// stack
// title -> 1
// [has_title, a $ 1_object] t -> title

// heap
// 1: "the lliad" 

int main() {
    return 0;
}