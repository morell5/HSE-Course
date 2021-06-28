int** MinElement(int** first, int** last) {
    if (first == last) {
        return first;
    }
    int** min = first;
    while (++first != last) {
        // We have some difficulties in interpretation of the expression (*first < *min)
        if (*first < *min) {
            min = first;
        }
    }
    return min;
}

// Conclusion: we take a single algorithm and extended it a bunch of times -> now we have different domains
// we have figure out how all of it fits same syntactic pattern -> we can make it generic

int main() {
    return 0;
}