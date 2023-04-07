#include "test.hpp"


// void handle_post(const httplib::Request& req, httplib::Response& res) {

//    // Parse the JSON object from the request
//    json request = json::parse(req.body);
//    std::cout << "received from frontend" << std::endl;

//    // Print the JSON object to the console
//    std::cout << request.dump() << std::endl;

//    string OrderSide = request["side"];
//    string Symbol = request["ticker"];
//    string Quantity = request["amount"];
//    int QuantityInt = std::stoi(Quantity);

//    if(OrderSide == "buy"){
//        /*
//       try{
//                app.run(app.sessionId_, Symbol, QuantityInt);
//            }catch(std::exception & e){
//                std::cout << e.what();
//            }
//        */
//    }
//    //example if we want to get the value of shares
//    // Create a JSON object with a message, and send it back to the client
   
//    json response;
//    response["message"] = "pong";
//    res.set_header("Access-Control-Allow-Origin", "*");
//    res.status = 200;       //this one is not rly important but thats how the big boys check if the request was successful
//    res.set_content(response.dump(), "application/json");
// }

// void runEndPoint() {
//    httplib::Server endPoint;
//    endPoint.set_base_dir("./public");    // Set the base directory for the server
//    //Register your request handlers here

//    // This is an example of a POST request, sell is the route, currently for the sell button in trade.jsx line 41-58
//    endPoint.Post("/trade", [](const httplib::Request& req, httplib::Response& res) {
//        handle_post(req, res);
//    });    
//    std::cout << "Server listening on port 1234" << std::endl;
//    endPoint.listen("localhost", 1234);
// }

std::string userInput(){
    std::string str;
    // Taking in user's order
    getline(std::cin, str);

    // error checking
    istringstream in(str);
    std::string tstr;
    getline(in, tstr);
    if (in.fail()) throw (tstr.c_str());
    
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

    // checking corret formatting
    if (items.size() >= 3 && (items[0] == "Buy" || items[0] == "Sell") && isNum(items[1]))
    {
        return true;
    }
    return false;
}

int sums (int a, int b, int c) {
    return a+b+c;
}
