#pragma once
#include "json.hpp"
using json = nlohmann::json;

json pullOrderTable();
void connectToDB();