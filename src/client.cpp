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
void runServer() {
    httplib::Server server;
    
    //Register your request handlers here
    
    
    server.Get("/ping", [](const httplib::Request &, httplib::Response &res) {
        res.set_content("{\"message\": \"Hello Back from Backend!\"}", "application/json");
        cout<<"ping"<<endl;
    });
    std::cout << "Server listening on port 3000" << std::endl;
    server.listen("localhost", 1234);
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
        runServer();
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

