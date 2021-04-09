double* MinElement(double* first, double* last) {
    if (first == last) {
        return first;
    }
    double* min = first;
    while (++first != last) {
        // Problem: comparing double not actually get defined behaviour
        // Reason: floating point numbers have not a number 
        // Solution: add restrictions
        if (*first < *min) {
            min = first;
        }
    }
    return min;
}

int main() {
    return 0;
}