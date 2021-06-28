#include <iostream>
#include <concepts>
#include <vector>

int main() {
    // We should not expose implementation details
    // We should find generic constraints and expose them


    // Overconstraining is not a bad thing:
    // 1. start with abstractions that have strong requirements
    // 2. allows greater freedom in implementation details


    // We should not overgeneralizing templates
    // 1. weaker semantics; make it harder to reason about the behavior
    return 0;
}