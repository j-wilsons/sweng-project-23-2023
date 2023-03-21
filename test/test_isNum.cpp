#include "../include/client.hpp"


int test_isNum() {
    // valid
    if (!isNum("100")) return false;
    if (!isNum("200")) return false;
    if (!isNum("127632")) return false;
    if (!isNum("1")) return false;
    if (!isNum("2")) return false;
    if (!isNum("33333")) return false;
    if (!isNum("4444444444444444")) return false;

    // invalid
    if (isNum("-1")) return false;
    if (isNum("45.6")) return false;
    if (isNum("41-4")) return false;
    if (isNum(".1")) return false;
    if (isNum(".10.5")) return false;
    if (isNum("0.105")) return false;
    if (isNum("\"1\"")) return false;

    return true;
}

int main() {
    // if this value is not 0, the tests fail
    return (int)!test_isNum(); 
}
