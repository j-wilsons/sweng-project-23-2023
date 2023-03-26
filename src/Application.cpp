#include <quickfix/SessionID.h>
#include <quickfix/Message.h>
#include <quickfix/Session.h>
#include "Application.h"
#include <quickfix/MessageCracker.h>
#include "quickfix/fix44/ExecutionReport.h"
#include <quickfix/fix44/NewOrderSingle.h>
#include <string>
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
              FIX44::ExecutionReport orderReport = partialFillTradeSuccess(sessionID, quantity);
              FIX::Session::sendToTarget(orderReport, sessionID);
            }
        }
        Sleep(1000);//its in miliseconds
    }
    printf("All shares executed for %s \n", ticker.c_str());
}

void Application::run(const FIX::SessionID& sessionID,const std::string& Symbol, int Quantity)
{
    FIX44::NewOrderSingle newOrder = queryNewOrderSingle44(Symbol, Quantity, '1'); // 1 represents buy side, 2 represents sell side
    FIX::Session::sendToTarget(newOrder,  sessionID);  
}

FIX44::NewOrderSingle Application::queryNewOrderSingle44(const std::string& Symbol, int Quantity, char side) // side == 1 represents buy side, 2 represents sell side
{
    FIX44::NewOrderSingle newOrder(FIX::ClOrdID("12345"), FIX::Side(side), FIX::TransactTime(), FIX::OrdType(FIX::OrdType_LIMIT));
    newOrder.set(FIX::Symbol(Symbol));
    newOrder.set(FIX::OrderQty(Quantity));
    newOrder.set(FIX::Price(100.00));
    newOrder.set(FIX::HandlInst('1'));
    newOrder.set(FIX::TimeInForce(FIX::TimeInForce_DAY));
    return newOrder;
}

FIX44::NewOrderSingle Application::queryNewOrderMarket(const std::string& Symbol, int Quantity, char side) // side == 1 represents buy side, 2 represents sell side
{
    FIX44::NewOrderSingle newOrder(FIX::ClOrdID("12345"), FIX::Side(side), FIX::TransactTime(), FIX::OrdType(FIX::OrdType_MARKET));
    newOrder.set(FIX::Symbol(Symbol));
    newOrder.set(FIX::OrderQty(Quantity));
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
    std::cout << "\nTrade Successfully Completed\n";
    return orderReport;
}
FIX44::ExecutionReport Application::partialFillTradeSuccess(const FIX::SessionID& sessionID, int quantity){
    FIX44::ExecutionReport orderReport(FIX::OrderID("12345"),
                                        FIX::ExecID("I"),
                                        FIX::ExecType('F'),
                                        FIX::OrdStatus('1'),
                                        FIX::Side('1'),
                                        FIX::LeavesQty(100-quantity),
                                        FIX::CumQty(100),
                                        FIX::AvgPx(5));
    std::cout << "Trade partially filled\n";
    return orderReport;
 }