#include "test.hpp"


int test_extract_key() {
    std::string stuff = R"(
        {
            "quoteResponse": {
                "result": [
                    {
                        "one": 1,
                        "two": 2,
                        "three": 3,
                        "four": 4,
                        "another": 1029239
                    }
                ]
            },
            "eggs": 20,
            "hens": 101,
            "quoteResponshe": {
                "uh oh": 666
            },
            "hello world": "today is a great day! i went outside and ate an apple, then spontaneously combusted"
        }
    )";

    // valid
    assert(extract_key(stuff, "another") == 1029239);
    assert(extract_key(stuff, "four") == 4);
    assert(extract_key(stuff, "two") == 2);
    assert(extract_key(stuff, "one") == 1);
    assert(extract_key(stuff, "three") == 3);

    // invalid
    assert(std::isnan(extract_key(stuff, "yet another")));
    assert(std::isnan(extract_key(stuff, "eggs")));
    assert(std::isnan(extract_key(stuff, "hens")));
    assert(std::isnan(extract_key(stuff, "1")));
    assert(std::isnan(extract_key(stuff, "ONE")));

    return true;
}

int main() {
    // if this value is not 0, the tests fail
    return (int)!test_extract_key(); 
}
