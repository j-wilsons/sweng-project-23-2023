#include "Application.h"
#include "DatabaseManager.h"
#include <chrono>
#include <thread>
#include <vector>
#include <cstdio>
#include <httplib.h>
#include <string.h>
#include <iostream>
#include <string>
#include "json.hpp"
#include <algorithm>
#include "quickfix/fix44/ExecutionReport.h"

using json = nlohmann::json;

std::map<double, std::queue<FIX44::NewOrderSingle>> create_empty_orderbook()
{
    return std::map<double, std::queue<FIX44::NewOrderSingle>>();
}

struct Stock
{
    std::string stock_Ticker;
    std::map<double, std::queue<FIX44::NewOrderSingle>> buy_orderbook;
    std::map<double, std::queue<FIX44::NewOrderSingle>> sell_orderbook;

    // constructor
    Stock(std::string stockTicker) : stock_Ticker(stockTicker)
    {
        buy_orderbook = create_empty_orderbook();
        sell_orderbook = create_empty_orderbook();
    }
};

std::vector<Stock> createStockList()
{
    std::vector<Stock> stockList;
    stockList.emplace_back("IBM");
    stockList.emplace_back("NKE");
    stockList.emplace_back("TSLA");
    stockList.emplace_back("AMZN");
    stockList.emplace_back("META");
    stockList.emplace_back("MSFT");
    return stockList;
}

void printOrders(json allOrders)
{
    for (const auto &order : allOrders)
    {
        std::cout << "Order ID: " << order["id"] << std::endl;
        std::cout << "Side: " << order["side"] << std::endl;
        std::cout << "Price: " << order["price"] << std::endl;
        std::cout << "Quantity: " << order["quantity"] << std::endl;
        std::cout << "Username: " << order["username"] << std::endl;
        std::cout << "Ticker: " << order["ticker"] << std::endl;
        std::cout << "-----------------------" << std::endl;
    }
}

FIX44::NewOrderSingle createNewOrderSingle44(std::string ID, const std::string &Symbol, int Quantity, const std::string side, double Price)
{
    FIX::Side fixSide;
    if (side == "BUY")
    {
        fixSide = FIX::Side(FIX::Side_BUY);
    }
    else if (side == "SELL")
    {
        fixSide = FIX::Side(FIX::Side_SELL);
    }
    FIX44::NewOrderSingle newOrder(FIX::ClOrdID(ID), fixSide, FIX::TransactTime(), FIX::OrdType(FIX::OrdType_LIMIT));
    newOrder.set(FIX::Symbol(Symbol));
    newOrder.set(FIX::OrderQty(Quantity));
    newOrder.set(FIX::Price(Price));
    newOrder.set(FIX::HandlInst('1'));
    newOrder.set(FIX::TimeInForce(FIX::TimeInForce_DAY));
    return newOrder;
}

void print_ibm_orderbook_keys(const std::vector<Stock> &stockList)
{
    auto it = std::find_if(stockList.begin(), stockList.end(), [](const Stock &stock)
                           { return stock.stock_Ticker == "IBM"; });

    if (it != stockList.end())
    {
        std::cout << "Buy orderbook keys for IBM:\n";
        for (const auto &price_orders_pair : it->buy_orderbook)
        {
            double price = price_orders_pair.first;
            std::cout << "Price: " << price << "\n";
        }

        std::cout << "\nSell orderbook keys for IBM:\n";
        for (const auto &price_orders_pair : it->sell_orderbook)
        {
            double price = price_orders_pair.first;
            std::cout << "Price: " << price << "\n";
        }
    }
    else
    {
        std::cout << "IBM stock not found in stockList.\n";
    }
}

FIX44::ExecutionReport tradeSuccessful(const FIX::SessionID &sessionID, int CumQty, double price)
{
    FIX44::ExecutionReport orderReport(FIX::OrderID("12345"),
                                       FIX::ExecID("I"),
                                       FIX::ExecType('F'),
                                       FIX::OrdStatus('2'),
                                       FIX::Side('1'),
                                       FIX::LeavesQty(0),
                                       FIX::CumQty(CumQty),
                                       FIX::AvgPx(price));
    std::cout << "\nTrade Successfully Completed\n";
    return orderReport;
}

void onMatch(FIX::SessionID &sessionID, int cumQty, double price){
    FIX44::ExecutionReport orderReport = tradeSuccessful(sessionID, cumQty, price);
    FIX::Session::sendToTarget(orderReport, sessionID);
}

void matchOrders(Stock &stock, FIX::SessionID &sessionID)
{
    try
    {
        auto &buy_orderbook = stock.buy_orderbook;
        auto &sell_orderbook = stock.sell_orderbook;

        bool matchFound = true;

        while (matchFound)
        {
            matchFound = false;

            if (!buy_orderbook.empty() && !sell_orderbook.empty())
            {
                auto highest_buy = buy_orderbook.rbegin();
                auto lowest_sell = sell_orderbook.begin();

                if (highest_buy->first >= lowest_sell->first)
                {
                    double matchedPrice = static_cast<double>(lowest_sell->first);
                    auto &buy_order = highest_buy->second.front();
                    auto &sell_order = lowest_sell->second.front();

                    /*
                     if (buy_order.getField(49) == sell_order.getField(49))
                    {
                        // Skip the current order and continue with the next
                        continue;
                    }
                    */
                    
                    
                    matchFound = true;
                    std::cout << "\n\nMATCH FOUND "
                              << "\n";
                    std::cout << " buy OrderQuantity: " << buy_order.getField(38) << ", ";
                    std::cout << " sell OrderQuantity: " << sell_order.getField(38) << ", ";

                    int buy_quantity, sell_quantity;
                    buy_quantity = stoi(buy_order.getField(38));
                    sell_quantity = stoi(sell_order.getField(38));

                    int matchedQty = min(buy_quantity, sell_quantity);
                    buy_quantity -= matchedQty;
                    sell_quantity -= matchedQty;

                    if (buy_quantity == 0)
                    {
                        
                        int orderId = stoi(buy_order.getField(11));
                        std::cout << "\n deleting order " << orderId << " from DB \n ";
                        deleteOrder(orderId); // Delete the finished order from the database
                        
                        highest_buy->second.pop();
                        if (highest_buy->second.empty())
                        {
                            auto key_to_erase = highest_buy->first;
                            buy_orderbook.erase(key_to_erase);
                        }
                        onMatch(sessionID, buy_quantity, matchedPrice);
                    }
                    else
                    {
                        int orderId = stoi(buy_order.getField(11));
                        std::cout << "\n reducing quantity to  " << buy_quantity << " for order "<< orderId ;
                        sell_order.setField(FIX::OrderQty(buy_quantity));
                        updateOrderQuantity(orderId, buy_quantity);
                    }

                    if (sell_quantity == 0)
                    {
                        int orderId = stoi(sell_order.getField(11));
                        std::cout << "\n deleting order " << orderId << " from DB \n ";
                        deleteOrder(orderId); // Delete the finished order from the database
                        
                        lowest_sell->second.pop();
                        if (lowest_sell->second.empty())
                        {
                            sell_orderbook.erase(lowest_sell->first);
                        }
                        onMatch(sessionID, buy_quantity, matchedPrice);
                    }
                    else
                    {
                        int orderId = stoi(sell_order.getField(11));
                        std::cout << "\n reducing quantity to  " << sell_quantity << " for order "<< orderId ;
                        sell_order.setField(FIX::OrderQty(sell_quantity));
                        updateOrderQuantity(orderId, sell_quantity);
                    }
                }
            }
        }
    }
    catch (std::exception &e)
    {
        std::cout << e.what();
    }
};

void processOrders(const json &orders, std::vector<Stock> &stockList, FIX::SessionID &sessionID)
{
    try
    {
        for (const auto &order : orders)
        {
            std::string side = order["side"];
            std::string ticker = order["ticker"];
            double price = order["price"];
            int quantity = order["quantity"];
            std::string id = to_string(order["id"]);
            FIX44::NewOrderSingle fixOrder = createNewOrderSingle44(id, ticker, quantity, side, price);

            // Debug: Print order information
            std::cout << "Processing order for ticker: " << ticker << ", side: " << side << ", price: " << price << ", quantity: " << quantity << std::endl;

            // Find the stock in stockList by its ticker
            auto it = std::find_if(stockList.begin(), stockList.end(), [&ticker](const Stock &stock)
                                   { return stock.stock_Ticker == ticker; });

            // If the stock is found in the stockList
            if (it != stockList.end())
            {
                if (side == "BUY")
                {
                    it->buy_orderbook[price].push(fixOrder);
                }
                else if (side == "SELL")
                {
                    it->sell_orderbook[price].push(fixOrder);
                }
                matchOrders(*it, sessionID);
            }
        }
    }
    catch (std::exception &e)
    {
        std::cout << e.what();
    }
}

void display_ibm_orders(const std::vector<Stock> &stockList)
{
    auto it = std::find_if(stockList.begin(), stockList.end(), [](const Stock &stock)
                           { return stock.stock_Ticker == "IBM"; });

    if (it != stockList.end())
    {
        std::cout << "Buy orders for IBM:\n";
        for (const auto &price_orders_pair : it->buy_orderbook)
        {
            double price = price_orders_pair.first;
            const std::queue<FIX44::NewOrderSingle> &orders = price_orders_pair.second;

            std::queue<FIX44::NewOrderSingle> orders_copy = orders;
            while (!orders_copy.empty())
            {
                const FIX44::NewOrderSingle &order = orders_copy.front();
                // Print order details here, e.g., orderID, side, price, quantity, etc.
                FIX::ClOrdID clOrdID;
                std::cout << "OrderID: " << order.getField(clOrdID) << ", ";
                std::cout << "Side: buy, ";
                std::cout << "Price: " << price << ", ";
                FIX::Quantity quantity;
                std::cout << "Quantity: " << order.getField(quantity) << "\n";
                orders_copy.pop();
            }
        }
    }
    else
    {
        std::cout << "IBM stock not found in stockList.\n";
    }
}

void startEngine(FIX::SessionID &sessionID)
{
    connectToDB();
    json allOrders = pullOrderTable();
    //printOrders(allOrders);
    std::vector<Stock> stockList = createStockList();
    processOrders(allOrders, stockList, sessionID);
    //print_ibm_orderbook_keys(stockList);
}
