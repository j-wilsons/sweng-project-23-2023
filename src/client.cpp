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
using json = nlohmann::json;
using namespace std;
int a=0;
std::string userInput(){
    std::string str;
    getline(std::cin, str);              // Taking in user's order
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
void handle_ping(const httplib::Request& req, httplib::Response& res) {
    std::cout<<"ping"<<std::endl;

    // Create a JSON object with a message, and send it back to the client
    json response;
    //message is the key, and pong is the value
    response["message"] = "pong";

    res.status = 200;       //this one is not rly important but thats how the big boys check if the request was successful
    res.set_header("Access-Control-Allow-Origin", "*"); // This is required for CORS
    res.set_content(response.dump(), "application/json");    // Set the content of the response to the JSON object
}
void handle_post(const httplib::Request& req, httplib::Response& res, Application app) {
    // Parse the JSON object from the request
    json request = json::parse(req.body);
    std::cout << "received from frontend" << std::endl;

    // Print the JSON object to the console
    std::cout << request.dump() << std::endl;

    string OrderSide = request["side"];
    string Symbol = request["ticker"];
    string Quantity = request["amount"];
    int QuantityInt = std::stoi(Quantity);

    if(OrderSide == "buy"){
       try{
                app.run(app.sessionId_, Symbol, QuantityInt);
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

void runEndPoint(Application& app) {
    httplib::Server endPoint;
    endPoint.set_base_dir("./public");    // Set the base directory for the server
    //Register your request handlers here

    // This is an example of a POST request, sell is the route, currently for the sell button in trade.jsx line 41-58
    endPoint.Post("/trade", [&app](const httplib::Request& req, httplib::Response& res) {      
        handle_post(req, res, app);
    });    
    std::cout << "Server listening on port 1234" << std::endl;
    endPoint.listen("localhost", 1234);
}
int main()
{
    try
    {
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

