#ifndef MATCHING_ENGINE_H
#define MATCHING_ENGINE_H
#include <quickfix/Application.h>
#include "Application.h"
#include <chrono>
#include <thread>
#include <vector>
#include <cstdio>
#include <string.h>
#include <iostream>
#include <string>
#include <unordered_map>
#include <queue>
#include "json.hpp"
#include <iostream>

using json = nlohmann::json;

std::unordered_map<double, std::queue<FIX44::NewOrderSingle>> create_empty_orderbook();
struct Stock {
    std::string stock_Ticker;
    std::unordered_map<double, std::queue<FIX44::NewOrderSingle>> buy_orderbook;
    std::unordered_map<double, std::queue<FIX44::NewOrderSingle>> sell_orderbook;

    // constructor
    Stock(std::string stockTicker);
};
void printOrders(json allOrders);
void processOrders(const json& orders, std::vector<Stock>& stockList, const FIX::SessionID &sessionID);
void startEngine(FIX::SessionID &sessionID);
std::vector<Stock> createStockList();


#endif MATCHING_ENGINE_H
