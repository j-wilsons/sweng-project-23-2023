
#include <quickfix/Message.h>
#include <quickfix/Session.h>
#include <quickfix/SessionSettings.h>
#include <quickfix/FileStore.h>
#include <quickfix/ThreadedSocketAcceptor.h>
#include "quickfix/FileLog.h"
#include "quickfix/SocketAcceptor.h"
#include "Application.h"
#include <string>
#include <string.h>
#include "quickfix/SocketInitiator.h"
#include <httplib.h>
#include "json.hpp"
#include "DataBaseManager.h"
#include "OrderStatus.h"

std::unordered_map<std::string, std::string> orderStatusMap;
using json = nlohmann::json;
using namespace std;
int a=0;
std::string userInput(){
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
std::vector<std::string> unorderedMapKeysToList(const std::unordered_map<std::string, string>& input_map) {
    std::vector<std::string> keys_list;
    keys_list.reserve(input_map.size());

    for (const auto& pair : input_map) {
        keys_list.push_back(pair.first);
    }

    return keys_list;
}

json convertMapToJson(const std::unordered_map<std::string, std::string>& orderStatusMap) {

    json jsonObject;

    for (const auto& entry : orderStatusMap) {
        jsonObject[entry.first] = entry.second;
    }

    return jsonObject;
}

json listToJson(const std::vector<std::string>& list) {
    nlohmann::json json_list = nlohmann::json::array();

    for (const auto& item : list) {
        int number = std::stoi(item);
        json_list.push_back(number);
    }

    return json_list;
}

void handle_ping(const httplib::Request& req, httplib::Response& res) {
    std::cout<<"ping"<<std::endl;
    std::vector<std::string> keys = unorderedMapKeysToList(orderStatusMap);
    // Create a JSON object with a message, and send it back to the client
    json response;
    response["filled"] = listToJson(keys);
    //message is the key, and pong is the value
    std::cout << "Converted JSON: " << response.dump() << std::endl;

    res.set_header("Access-Control-Allow-Origin", "*"); // This is required for CORS
    res.status = 200;       //this one is not rly important but thats how the big boys check if the request was successful
    res.set_content(response.dump(), "application/json");    // Set the content of the response to the JSON object
}

void handle_post(const httplib::Request& req, httplib::Response& res, Application app) {
    // Parse the JSON object from the request
    json request = json::parse(req.body);
    std::cout << "received from frontend" << std::endl;

    // Print the JSON object to the console
    std::cout << request.dump() << std::endl;
    try
    {
        /* code */
    string customOrderID = request["orderID"];
    string OrderSide = request["side"];
    std::cout << "side" << std::endl;
    string Symbol = request["ticker"];
    std::cout << "symbol" << std::endl;
    string Quantity = request["amount"];
    int QuantityInt = std::stoi(Quantity);
    std::cout << "quantity" << std::endl;
    string price = request["price"];
    double Dprice = std::stod(price);
    std::cout << "price" << std::endl;
    // double price = std::stoi(priceString);
    std::cout << "orderside" << OrderSide << std::endl; 
    if(OrderSide == "buy"){
       try{
                std::cout << "buy order came through" << std::endl;
                app.sendBuyOrder(app.sessionId_, Symbol, QuantityInt, Dprice, customOrderID);
            }catch(std::exception & e){
                std::cout << e.what();
            }
    }else if(OrderSide == "sell"){
        try{
                app.sendSellOrder(app.sessionId_, Symbol, QuantityInt,Dprice, customOrderID);
            }catch(std::exception & e){
                std::cout << e.what();
            }
    }
    //example if we want to get the value of shares
    // Create a JSON object with a message, and send it back to the client
    json response;
    response["message"] = "pong";
    res.set_header("Access-Control-Allow-Origin", "*");
    res.status = 200;       //this one is not rly important but thats how the big boys check if the request was successful
    res.set_content(response.dump(), "application/json");
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    

}

void runEndPoint(Application& app) {
    httplib::Server endPoint;
    endPoint.set_base_dir("./public");    // Set the base directory for the server
    //Register your request handlers here

    // This is an example of a POST request, sell is the route, currently for the sell button in trade.jsx line 41-58
    endPoint.Post("/trade", [&app](const httplib::Request& req, httplib::Response& res) {      
        handle_post(req, res, app);
    });    
    endPoint.Get("/ping", handle_ping);

    std::cout << "Server listening on port 1234" << std::endl;
    endPoint.listen("localhost", 1234);
}
int main()
{
    try
    {   
        connectToDB();
        pullOrderTable();
        FIX::SessionSettings settings("../../src/client.cfg");
        Application application;
        FIX::FileStoreFactory storeFactory(settings);
        FIX::ScreenLogFactory logFactory(settings);
        FIX::SocketInitiator initiator(application, storeFactory, settings, logFactory);
        initiator.start();
        //std::thread serverThread(runServer);
        runEndPoint(application);
        while (true) {
            string Order;
            do{
                
                Order = userInput();
                if (isCorrectForm(Order))
                {
                    break;
                }
                cout << "----Order is not Correctly formatted----" << endl;
                cout << "Please follow: Buy/Sell Quantity CompanyName" << endl;
            } while (true);

            string Symbol, Action;
            int Quantity;

            std::istringstream iss(Order);
            iss >> Action >> Quantity >> Symbol;
            
            try{
                application.run(application.sessionId_, Symbol, Quantity);
            }catch(std::exception & e){
                std::cout << e.what();
            }
        }
        return 0;
    }
    catch (FIX::ConfigError& e)
    {
        std::cout << e.what();
        while (true) {
            //FIX::process_sleep(1);
        }
        return 1;
    }
}
