#include <quickfix/SessionID.h>
#include <quickfix/Message.h>
#include <quickfix/Session.h>
#include "Application.h"
#include <quickfix/MessageCracker.h>
#include "quickfix/fix44/ExecutionReport.h"
#include <quickfix/fix44/NewOrderSingle.h>
#include <string>
#include <vector>
#include "curl/curl.h"
#include <iostream>
#include "json.hpp"
#include <windows.h>           // for windows for sleeping

using namespace std;

void Application::onCreate(const FIX::SessionID&)
{

}

void Application::onLogon(const FIX::SessionID& sessionID)
{
	std::cout << std::endl << "Logon - SessionID:   " << sessionID << std::endl;
	sessionId_ = sessionID;
}

void Application::onLogout(const FIX::SessionID& sessionID)
{
}

void Application::toAdmin(FIX::Message&, const FIX::SessionID&)
{
}

void Application::toApp(FIX::Message&, const FIX::SessionID&) throw(FIX::DoNotSend)
{
}

void Application::fromApp( const FIX::Message& message, const FIX::SessionID& sessionID )
throw( FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::UnsupportedMessageType )
{
    std::string senderCompID;
    std::string timeId;
    senderCompID = message.getHeader().getField(FIX::FIELD::SenderCompID);
    timeId = message.getField(FIX::FIELD::TransactTime);


     if (senderCompID == "CLIENT")
    {
        crack( message, sessionID );
        int orderQty = std::stoi(message.getField(FIX::FIELD::OrderQty));
        FIX44::ExecutionReport orderReport = tradeSuccessful(sessionID, timeId);
        FIX::Session::sendToTarget(orderReport,  sessionID);
    }
    else if (senderCompID == "SERVER")
    {
       
    }else{
        std::cout << std::endl << "UNKNOWN SENDER" << std::endl;
    }
      

}

void Application::onMessage(const FIX44::NewOrderSingle& message, const FIX::SessionID& sessionID)
{   
    orderSingleMessage=message;
    
    //checkfields, <todo>
    /*
    if(message.isSetField(49)){
        std::cout<<"Client Order Received"<<std::endl;
    }else{
        std::cout<<"missing"<<std::endl;
    }
    if(message.isSetField(8)){
        std::cout<<"Client Order Received"<<std::endl;
    }else{
        std::cout<<"missing"<<std::endl;
    }*/
    int quantity = stoi(message.getField(38));
    std::string ticker = message.getField(55);
    fakeExec(ticker, quantity, sessionID);
    
    
}

void Application::fakeExec(std::string& ticker, int quantity, const FIX::SessionID& sessionID){
    int randomNumber;
    while(quantity >= 5) {
        randomNumber = rand()%(quantity+ 1);
        //randomNumber = 0 + (rand() % quantity);
        if(randomNumber>0){
            quantity -= randomNumber;
            printf("%d shares traded\n", randomNumber);
            if(quantity >= 5){
              
            }
        }
        Sleep(1000);//its in miliseconds
    }
    printf("All shares executed for %s \n", ticker.c_str());
}

void Application::run(const FIX::SessionID& sessionID,const std::string& Symbol, int Quantity, std::string id)
{
    FIX44::NewOrderSingle newOrder = queryNewOrderSingle44(Symbol, Quantity, '1', id); // 1 represents buy side, 2 represents sell side
    FIX::Session::sendToTarget(newOrder,  sessionID);  
}

void Application::sendBuyOrder(const FIX::SessionID& sessionID,const std::string& Symbol, int Quantity, std::string id)
{
    FIX44::NewOrderSingle newOrder = queryNewOrderSingle44(Symbol, Quantity, '1', id); // 1 represents buy side, 2 represents sell side
    FIX::Session::sendToTarget(newOrder,  sessionID);  
}

void Application::sendSellOrder(const FIX::SessionID& sessionID,const std::string& Symbol, int Quantity, std::string id)
{
    FIX44::NewOrderSingle newOrder = queryNewOrderSingle44(Symbol, Quantity, '2', id); // 1 represents buy side, 2 represents sell side
    FIX::Session::sendToTarget(newOrder,  sessionID);  
}

FIX44::NewOrderSingle Application::queryNewOrderSingle44(const std::string& Symbol, int Quantity, char side, std::string id) // side == 1 represents buy side, 2 represents sell side
{
    FIX44::NewOrderSingle newOrder(FIX::ClOrdID(id), FIX::Side(side), FIX::TransactTime(), FIX::OrdType('2'));
    newOrder.set(FIX::Symbol(Symbol));
    newOrder.set(FIX::OrderQty(Quantity));
    newOrder.set(FIX::Price(100.00));
    newOrder.set(FIX::HandlInst('1'));
    newOrder.set(FIX::TimeInForce(FIX::TimeInForce_DAY));
    return newOrder;
}

FIX44::NewOrderSingle Application::queryNewOrderMarket(const std::string& Symbol, int Quantity, char side, std::string id) // side == 1 represents buy side, 2 represents sell side
{
    FIX44::NewOrderSingle newOrder(FIX::ClOrdID(id), FIX::Side(side), FIX::TransactTime(), FIX::OrdType('1'));
    newOrder.set(FIX::Symbol(Symbol));
    newOrder.set(FIX::OrderQty(Quantity));
    newOrder.set(FIX::HandlInst('1'));
    newOrder.set(FIX::TimeInForce(FIX::TimeInForce_DAY));
    newOrder.set(FIX::TransactTime());
    return newOrder;
}

FIX44::ExecutionReport Application::tradeSuccessful(const FIX::SessionID& sessionID, std::string id){
    FIX44::ExecutionReport orderReport(FIX::OrderID(id),
                                        FIX::ExecID("I"),
                                        FIX::ExecType('F'),
                                        FIX::OrdStatus('2'),
                                        FIX::Side('1'),
                                        FIX::LeavesQty(0),
                                        FIX::CumQty(100),
                                        FIX::AvgPx(5));
    std::cout << "\nTrade Successfully Completed\n";
    return orderReport;
}
FIX44::ExecutionReport Application::partialFillTradeSuccess(const FIX::SessionID& sessionID, int quantity, int totalQuant, std::string id){
    FIX44::ExecutionReport orderReport(FIX::OrderID(id),
                                        FIX::ExecID("I"),
                                        FIX::ExecType('F'),
                                        FIX::OrdStatus('1'),
                                        FIX::Side('1'),
                                        FIX::LeavesQty(totalQuant-quantity),
                                        FIX::CumQty(quantity),
                                        FIX::AvgPx(5));
    std::cout << "Trade partially filled\n";
    return orderReport;
}

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

double extract_key(const string& json_str, string key) {
    nlohmann::json json = nlohmann::json::parse(json_str);
    return json["quoteResponse"]["result"][0][key];
}

//takes in vector with tickers e,g: AAPL, returns vector of JSON strings containing AAPL stock data
vector<string> Application::marketData(vector<string> symbols)
{
    std::vector<std::string> responseVec;
    try
    {
        std::string url_base = "https://query1.finance.yahoo.com/v7/finance/quote?symbols=";
        std::string response;

        for (const auto &symbol : symbols)
        {
            std::string url = url_base + symbol;
            CURL *curl = curl_easy_init();
            if (curl)
            {
                curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
                curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
                curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
                CURLcode res = curl_easy_perform(curl);

                // if (res != CURLE_OK)
                //     std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
                // else
                //     std::cout << "Response:" << std::endl << response << std::endl << std::endl;
                curl_easy_cleanup(curl);
            }

            responseVec.push_back(response);
        }
        return responseVec;

    }
    catch (FIX::ConfigError& e)
    { 
        std::cout << e.what();
        std::vector<std::string> vec = {"Curl Error"};
        return vec;
    }
}
