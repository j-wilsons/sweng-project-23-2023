#include <quickfix/SessionID.h>
#include <quickfix/Message.h>
#include <quickfix/Session.h>
#include "Application.h"
#include <quickfix/MessageCracker.h>
#include "quickfix/fix44/ExecutionReport.h"
#include <quickfix/fix44/NewOrderSingle.h>

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
    crack(message, sessionID);

}
void Application::onMessage(const FIX44::NewOrderSingle& message, const FIX::SessionID& sessionID)
{
    orderSingleMessage=message;
    std::cout << "message got: " << message << std::endl;
    
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
