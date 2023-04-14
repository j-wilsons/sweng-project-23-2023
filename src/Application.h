#pragma once
#include <quickfix/Message.h>
#include <quickfix/Session.h>
#include <quickfix/SessionSettings.h>
#include <quickfix/FileStore.h>
#include <quickfix/ThreadedSocketAcceptor.h>
#include "quickfix/FileLog.h"
#include "quickfix/MessageCracker.h"
#include "quickfix/SocketAcceptor.h"
#include "Application.h"
#include <quickfix/fix44/NewOrderSingle.h>


class Application : public FIX::Application, public FIX::MessageCracker
{
public:
    virtual ~Application() {};
    void onCreate(const FIX::SessionID&);
    void onLogon(const FIX::SessionID& sessionID);
    void onLogout(const FIX::SessionID& sessionID);
    void toAdmin(FIX::Message&, const FIX::SessionID&);
    void toApp(FIX::Message&, const FIX::SessionID&)
        throw(FIX::DoNotSend);
    void fromAdmin(const FIX::Message&, const FIX::SessionID&)
        throw(FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::RejectLogon) {}
    void fromApp(const FIX::Message& message, const FIX::SessionID& sessionID)
        throw(FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::UnsupportedMessageType);
    void run(const FIX::SessionID& sessionID,const std::string& Symbol, int Quantity);
    void sendBuyOrder(const FIX::SessionID &sessionID, const std::string &Symbol, int Quantity, double price);
    void sendSellOrder(const FIX::SessionID &sessionID, const std::string &Symbol, int Quantity, double price);
    FIX44::NewOrderSingle Application::queryNewOrderSingle44(const std::string &Symbol, int Quantity, char side, double Price);
    FIX44::NewOrderSingle Application::queryNewOrderMarket(const std::string& Symbol, int Quantity, char side);
    FIX::SessionID sessionId_;
    FIX44::NewOrderSingle orderSingleMessage;
    FIX44::ExecutionReport Application::tradeSuccessful(const FIX::SessionID& sessionID);
    FIX44::ExecutionReport Application::partialFillTradeSuccess(const FIX::SessionID& sessionID, int quantity);
    void onMessage(const FIX44::NewOrderSingle& message, const FIX::SessionID& sessionID);
    void onMessage(const FIX44::ExecutionReport& message, const FIX::SessionID& sessionID);
    void fakeExec(std::string& ticker, int quantity, const FIX::SessionID& sessionID);
    std::vector<std::string> marketData(std::vector<std::string> symbols);
}; 

double extract_key(const std::string& json_str, std::string key);
