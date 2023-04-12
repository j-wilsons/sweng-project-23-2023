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
#include <windows.h> // for windows for sleeping
#include "DataBaseManager.h"

using namespace std;

void Application::onCreate(const FIX::SessionID &)
{
}

void Application::onLogon(const FIX::SessionID &sessionID)
{
    std::cout << std::endl
              << "Logon - SessionID:   " << sessionID << std::endl;
    sessionId_ = sessionID;
}

void Application::onLogout(const FIX::SessionID &sessionID)
{
}

void Application::toAdmin(FIX::Message &, const FIX::SessionID &)
{
}

void Application::toApp(FIX::Message &, const FIX::SessionID &) throw(FIX::DoNotSend)
{
}

void Application::fromApp(const FIX::Message &message, const FIX::SessionID &sessionID) throw(FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::UnsupportedMessageType)
{
   crack(message, sessionID);
}

void Application::onMessage(const FIX44::NewOrderSingle &message, const FIX::SessionID &sessionID)
{
    std::string senderCompID;
    senderCompID = message.getHeader().getField(FIX::FIELD::SenderCompID);
    if (senderCompID == "CLIENT")
    {

        try
        {   
            std::cout << "Extracting deets from order "<< std::endl;
            // Extract order details from the message
            int orderId = stoi(message.getField(11));
            std::cout << "id" << std::endl;
            string side = message.getField(54);
            if (side == "1")
            {
                side = "BUY";
            }
            else if (side == "2")
            {
                side = "SELL";
            }
            std::cout << "side" << std::endl;
            double price = stod(message.getField(44));
            std::cout << "price" << std::endl;
            int quantity = stoi(message.getField(38));
            std::cout << "quanitty" << std::endl;
            string timestamp = message.getField(60);
            std::cout << "timer" << std::endl;
            string ticker = message.getField(55);
            std::cout << "ticker" << std::endl;
            string username = message.getHeader().getField(FIX::FIELD::SenderCompID); // Add your logic to extract username from the message
            std::cout << "name" << std::endl;
            std::cout << "\nSENDING TO DATABASE\n " << std::endl;
            // Send the order details to the database
            
            addOrderToDatabase(orderId, side, price, quantity, timestamp, username, ticker);
        }
        catch (const std::exception &e)
        {
            std::cout << "Error processing message: " << e.what() << std::endl;
        }
        // FIX44::ExecutionReport orderReport = tradeSuccessful(sessionID);
        // FIX::Session::sendToTarget(orderReport,  sessionID);
    }
    else if (senderCompID == "SERVER")
    {
        std::cout << "Came from server" << std::endl;
    }
    else
    {
        std::cout << std::endl
                  << "UNKNOWN SENDER" << std::endl;
    }
}

void Application::fakeExec(std::string &ticker, int quantity, const FIX::SessionID &sessionID)
{
    int randomNumber;
    while (quantity >= 5)
    {
        randomNumber = rand() % (quantity + 1);
        // randomNumber = 0 + (rand() % quantity);
        if (randomNumber > 0)
        {
            quantity -= randomNumber;
            printf("%d shares traded\n", randomNumber);
            if (quantity >= 5)
            {
                FIX44::ExecutionReport orderReport = partialFillTradeSuccess(sessionID, quantity);
                FIX::Session::sendToTarget(orderReport, sessionID);
            }
        }
        Sleep(1000); // its in miliseconds
    }
    printf("All shares executed for %s \n", ticker.c_str());
}

void Application::run(const FIX::SessionID &sessionID, const std::string &Symbol, int Quantity)
{
    // FIX44::NewOrderSingle newOrder = queryNewOrderSingle44(Symbol, Quantity, '1'); // 1 represents buy side, 2 represents sell side
    // FIX::Session::sendToTarget(newOrder,  sessionID);
}

void Application::sendBuyOrder(const FIX::SessionID &sessionID, const std::string &Symbol, int Quantity, double price)
{
    FIX44::NewOrderSingle newOrder = queryNewOrderSingle44(Symbol, Quantity, '1', price); // 1 represents buy side, 2 represents sell side
    FIX::Session::sendToTarget(newOrder, sessionID);
}

void Application::sendSellOrder(const FIX::SessionID &sessionID, const std::string &Symbol, int Quantity, double price)
{
    FIX44::NewOrderSingle newOrder = queryNewOrderSingle44(Symbol, Quantity, '2', price); // 1 represents buy side, 2 represents sell side
    FIX::Session::sendToTarget(newOrder, sessionID);
}

FIX44::NewOrderSingle Application::queryNewOrderSingle44(const std::string &Symbol, int Quantity, char side, double Price) // side == 1 represents buy side, 2 represents sell side
{
    FIX::Side fix_side;
    if (side == '1')
    {
        fix_side = FIX::Side(FIX::Side_BUY);
    }
    else if (side == '2')
    {
        fix_side = FIX::Side(FIX::Side_SELL);
    }
    else
    {
        std::cout << "\nError on sideChecker\n";
    }

    FIX44::NewOrderSingle newOrder(FIX::ClOrdID("12345"), fix_side, FIX::TransactTime(), FIX::OrdType(FIX::OrdType_LIMIT));
    newOrder.set(FIX::Symbol(Symbol));
    newOrder.set(FIX::OrderQty(Quantity));
    newOrder.set(FIX::Price(Price));
    newOrder.set(FIX::HandlInst('1'));
    newOrder.set(FIX::TimeInForce(FIX::TimeInForce_DAY));
    return newOrder;
}

FIX44::NewOrderSingle Application::queryNewOrderMarket(const std::string &Symbol, int Quantity, char side) // side == 1 represents buy side, 2 represents sell side
{
    FIX44::NewOrderSingle newOrder(FIX::ClOrdID("12345"), FIX::Side(), FIX::TransactTime(), FIX::OrdType(FIX::OrdType_MARKET));
    newOrder.set(FIX::Symbol(Symbol));
    newOrder.set(FIX::OrderQty(Quantity));
    newOrder.set(FIX::HandlInst('1'));
    newOrder.set(FIX::TimeInForce(FIX::TimeInForce_DAY));
    return newOrder;
}

FIX44::ExecutionReport Application::tradeSuccessful(const FIX::SessionID &sessionID)
{
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
FIX44::ExecutionReport Application::partialFillTradeSuccess(const FIX::SessionID &sessionID, int quantity)
{
    FIX44::ExecutionReport orderReport(FIX::OrderID("12345"),
                                       FIX::ExecID("I"),
                                       FIX::ExecType('F'),
                                       FIX::OrdStatus('1'),
                                       FIX::Side('1'),
                                       FIX::LeavesQty(100 - quantity),
                                       FIX::CumQty(100),
                                       FIX::AvgPx(5));
    std::cout << "Trade partially filled\n";
    return orderReport;
}

size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string *)userp)->append((char *)contents, size * nmemb);
    return size * nmemb;
}

double extract_key(const string& json_str, string key) {
    try {
        nlohmann::json json = nlohmann::json::parse(json_str);
        return json["quoteResponse"]["result"][0][key];
    } catch (exception e) {
        cerr << e.what();
        return NAN;
    }


// takes in vector with tickers e,g: AAPL, returns vector of JSON strings containing AAPL stock data
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
    catch (FIX::ConfigError &e)
    {
        std::cout << e.what();
        std::vector<std::string> vec = {"Curl Error"};
        return vec;
    }
}
