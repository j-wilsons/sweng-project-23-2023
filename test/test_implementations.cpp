#include "test.hpp"


std::string userInput()
{
    std::string str;
    // Taking in user's order
    getline(std::cin, str);

    // error checking
    istringstream in(str);
    std::string tstr;
    getline(in, tstr);
    if (in.fail())
        throw(tstr.c_str());
    return str;
}

bool isNum(string input)
{
    for (std::size_t i = 0; i < input.size(); i++)
    {
        if (isdigit(input[i]) == 0)
        {
            return false;
        }
    }
    return true;
}

bool isCorrectForm(string input)
{
    // tokenise
    string item;
    vector<string> items;
    stringstream ss(input);
    while (std::getline(ss, item, ' '))
    {
        items.push_back(item);
    }

    // checking correct formatting
    if (items.size() >= 3 && (items[0] == "Buy" || items[0] == "Sell") && isNum(items[1]))
    {
        return true;
    }
    return false;
}

int sums(int a, int b, int c)
{
    return a + b + c;
}

double extract_key(const string& json_str, string key) {
    try {
        nlohmann::json json = nlohmann::json::parse(json_str);
        return json["quoteResponse"]["result"][0][key];
    } catch (exception e) {
        cerr << e.what() << std::endl;
        return NAN;
    }
}
