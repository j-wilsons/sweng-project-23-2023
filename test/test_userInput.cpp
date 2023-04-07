#include "test.hpp"

int test_userInput() {
    streambuf* orig = cin.rdbuf(); // store original std buffer
    string p;

    // strings able to be read from stdin
    vector<string> valids = {
        "test 1", 
        "test 2", 
        "AAAAAnnnnnnnnsewrewujklsdiioeusrojwuJOIUJIOJUWUHE8UIOUEnnn\\            nnnpppntsdteut\\tttthello world\\1", 
        "test 42rgf2qervqfqewve", 
        "IOADSIFMVL#E[OPREFKDOU   IEJCEJK[e]rqt  ||||``¬`¬¬¦¦ e[areP'DJI'PRS]]", 
        "ÁÉÍÓÚáúíóúdufv €¦¦",
        "     .     ", 
    };
    
    // strings unable to be read from stdin
    // other control characters do not return a failbit when reading, so they are omitted
    vector<string> invalids = {
        "\0", 
        "\n"
    };

    // valid
    for (auto x : valids) {
        istringstream in(x); // set iss buffer to string
        cin.rdbuf(in.rdbuf()); // change stdin buffer to iss buffer
        p = userInput(); // read from stdin
        assert(!in.fail());
        assert(p == x);
        printf("ANSWER: %s\n", p.c_str());
    }

    // invalid
    for (auto x : invalids) {
        istringstream in(x); // set iss buffer to string
        // in.setstate(std::ios::failbit);
        cin.rdbuf(in.rdbuf()); // change stdin buffer to iss buffer
        try {
            printf("TEST (BAD)\n");
            p = userInput(); // read from stdin
        } catch (...) {
            // assert(in.fail());
            // assert(p == x);
            printf("ANSWER (BAD): %s\n", p.c_str());
        }
    }

    cin.rdbuf(orig); // restore original std buffer
    return true;
}

int main() {
    // if this value is not 0, the tests fail
    return (int)!test_userInput(); 
}
