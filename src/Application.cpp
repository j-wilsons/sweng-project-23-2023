#include <quickfix/SessionID.h>
#include <quickfix/Message.h>
#include <quickfix/Session.h>
#include "Application.h"
#include <quickfix/MessageCracker.h>
#include "quickfix/fix44/ExecutionReport.h"
#include <quickfix/fix44/NewOrderSingle.h>
#include <string>
#include "curl/curl.h"
#include <iostream>
#include<windows.h>           // for windows for sleeping
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
    senderCompID = message.getHeader().getField(FIX::FIELD::SenderCompID);
     if (senderCompID == "CLIENT")
    {
        crack( message, sessionID );
        FIX44::ExecutionReport orderReport = tradeSuccessful(sessionID);
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
    fakeExec(ticker, quantity);
    
    
}

void Application::fakeExec(std::string& ticker, int quantity){
    int randomNumber;
    while(quantity >= 5) {
        randomNumber = rand()%(quantity+ 1);
        //randomNumber = 0 + (rand() % quantity);
        if(randomNumber>0){
            quantity -= randomNumber;
            printf("%d shares traded\n", randomNumber);
        }
        Sleep(1000);//its in miliseconds
    }
    printf("All shares executed for %s \n", ticker.c_str());
}

void Application::run(const FIX::SessionID& sessionID,const std::string& Symbol, int Quantity)
{
    FIX44::NewOrderSingle newOrder = queryNewOrderSingle44(Symbol, Quantity);
    FIX::Session::sendToTarget(newOrder,  sessionID);  
}

FIX44::NewOrderSingle Application::queryNewOrderSingle44(const std::string& Symbol, int Quantity)
{
    FIX44::NewOrderSingle newOrder(FIX::ClOrdID("12345"), FIX::Side(FIX::Side_BUY), FIX::TransactTime(), FIX::OrdType(FIX::OrdType_LIMIT));
    newOrder.set(FIX::Symbol(Symbol));
    newOrder.set(FIX::OrderQty(Quantity));
    newOrder.set(FIX::Price(100.00));
    newOrder.set(FIX::HandlInst('1'));
    newOrder.set(FIX::TimeInForce(FIX::TimeInForce_DAY));
    return newOrder;
}

FIX44::ExecutionReport Application::tradeSuccessful(const FIX::SessionID& sessionID){
    FIX44::ExecutionReport orderReport(FIX::OrderID("12345"),
                                        FIX::ExecID("I"),
                                        FIX::ExecType('F'),
                                        FIX::OrdStatus('2'),
                                        FIX::Side('1'),
                                        FIX::LeavesQty(0),
                                        FIX::CumQty(100),
                                        FIX::AvgPx(5));
    std::cout << "\nTrade Successful";
    return orderReport;
}

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}


int Application::marketData()
{
    try
    {

       std::string api_key = "EPD436H91DGONRID"; // replace with your own API key
    std::string url_base = "https://www.alphavantage.co/query?function=GLOBAL_QUOTE&symbol=";
    std::vector<std::string> symbols = {"AAPL", "GOOGL", "TSLA", "AMZN"}; // replace with your desired symbols

    for (const auto &symbol : symbols)
    {
        std::string url = url_base + symbol + "&apikey=" + api_key;
        std::string response;

        CURL *curl = curl_easy_init();
        if (curl)
        {
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
            CURLcode res = curl_easy_perform(curl);
            if (res != CURLE_OK)
                std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
            else
                std::cout << "Response:" << std::endl
                          << response << std::endl;
            curl_easy_cleanup(curl);
        }
    }
        

        FIX::SessionSettings settings("../../src/server.cfg");
        Application application;
        FIX::FileStoreFactory storeFactory(settings);
        FIX::ScreenLogFactory logFactory(settings);
        FIX::ThreadedSocketAcceptor acceptor(application, storeFactory, settings, logFactory);
        acceptor.start();
        while (true) {
     
        }
    
        return 0;
    }
    catch (FIX::ConfigError& e)
    { 
        std::cout << e.what();
        while (true) {
        }
        return 1;
    }

}

