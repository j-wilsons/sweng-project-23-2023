#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <cassert>
#include <limits.h>
#include <stddef.h>
#include <inttypes.h>
#include <stdint.h>
#include "../include/json.hpp"
using json = nlohmann::json;

// ! UNCOMMENT ONLY WHEN INCLUDING HTTPLIB.H
// https://stackoverflow.com/questions/34580472/alternative-to-ssize-t-on-posix-unconformant-systems
#if SIZE_MAX == UINT_MAX
typedef int ssize_t;        // common 32 bit case
#define SSIZE_MIN  INT_MIN
#define SSIZE_MAX  INT_MAX
#elif SIZE_MAX == ULONG_MAX
typedef long ssize_t;       // linux 64 bits
#define SSIZE_MIN  LONG_MIN
#define SSIZE_MAX  LONG_MAX
#elif SIZE_MAX == ULLONG_MAX
typedef long long ssize_t;  // windows 64 bits
#define SSIZE_MIN  LLONG_MIN
#define SSIZE_MAX  LLONG_MAX
#elif SIZE_MAX == USHRT_MAX
typedef short ssize_t;      // is this even possible?
#define SSIZE_MIN  SHRT_MIN
#define SSIZE_MAX  SHRT_MAX
#elif SIZE_MAX == UINTMAX_MAX
typedef uintmax_t ssize_t;  // last resort, chux suggestion
#define SSIZE_MIN  INTMAX_MIN
#define SSIZE_MAX  INTMAX_MAX
#else
#error platform has exotic SIZE_MAX
#endif

#include "../include/httplib.h" 


using namespace std;

std::string userInput();
bool isNum(string input);
bool isCorrectForm(string input);
int sums(int a, int b, int c);
//void handle_post();
//void runEndPoint();