// Overloading allows to extend the domain of the function
// Problem: overloading does not give you facilities to change function semantic

int* MinElement(int* first, int* last) {
    if (first == last) {
        return first;
    }
    int* min = first;
    while (++first != last) {
        if (*first < *min) {
            min = first;
        }
    }
    return min;
}

double* MinElement(double* first, double* last) {
    if (first == last) {
        return first;
    }
    double* min = first;
    while (++first != last) {
        if (*first < *min) {
            min = first;
        }
    }
    return min;
}

int main() {
    return 0;
}