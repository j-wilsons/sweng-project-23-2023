#include "test.hpp"


int test_example() {
    // valid
    if (sums(1, 2, 3) != 6) return false;

    // invalid
    if (sums(1, 2, 3) == 61) return false;

    return true;
}

int main() {
    // if this value is not 0, the tests fail
    return (int)!test_example(); 
}
