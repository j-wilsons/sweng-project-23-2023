#include <quickfix/Message.h>
#include <quickfix/Session.h>
#include <quickfix/SessionSettings.h>
#include <quickfix/FileStore.h>
#include <quickfix/ThreadedSocketAcceptor.h>
#include "quickfix/FileLog.h"
#include "quickfix/SocketAcceptor.h"
#include "Application.h"
#include <string>
#include "quickfix/SocketInitiator.h"

bool isCorrectForm(string input)
{
    // tokenise
    string item;
    vector<string> items;
    stringstream ss(input);
    while (getline(ss, item, ' '))
    {
        items.push_back(item);
    }

    // checking corret formatting
    if ((items.size() >= 3 && (items[0] == "Buy" || items[0] == "Sell") && isNum(items[1])) || items[0] == "quit")
    {
        return true;
    }
    return false;
}

string userInput(){
    string str;
    cout<<"Enter order: or type 'quit' to exit"<<endl;
    getline(cin, str);              // Taking in user's order
    return str;
}

int main()
{
    try
    {
        FIX::SessionSettings settings("../../client.cfg");
        Application application;
        FIX::FileStoreFactory storeFactory(settings);
        FIX::ScreenLogFactory logFactory(settings);
        FIX::SocketInitiator initiator(application, storeFactory, settings, logFactory);
        initiator.start();

        do //user input
        {
            Order = userInput();
            if (isCorrectForm(Order))
            {
                break;
            }
            cout << "----Order is not Correctly formatted----" << endl;
            cout << "Please follow: Buy/Sell Quantity CompanyName or type 'quit' to exit" << endl;
        } while (true) 
        if(Order=="quit"){
            return 0;
        }
        else{
            int OrderQuantity, Price;
            string Symbol;                               //input: string from the client
            stringstream ss(Order);
            ss >> Symbol >> OrderQuantity >> Price;

            Symbol = FIX::Symbol();
            OrderQuantity = FIX::OrderQty();
            Price = FIX::Price();
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

