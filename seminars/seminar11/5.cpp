template<typename T, typename A = ...>
class vector {
public:
    vector& operator=(const vector& rhs);
};

std::vector<int> v1{...};

std::vector<int> createVector() {
    return std::vector<int>{...};
}