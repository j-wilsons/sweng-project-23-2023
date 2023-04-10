#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <cassert>
#include <limits>
#include <stddef.h>
#include <inttypes.h>
#include <stdint.h>
#include "../include/json.hpp"
using json = nlohmann::json;
using namespace std;

string userInput();
bool isNum(string input);
bool isCorrectForm(string input);
int sums(int a, int b, int c);
double extract_key(const string& json_str, string key);
