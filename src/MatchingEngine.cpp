#include <quickfix/Application.h>
#include <quickfix/Message.h>
#include <quickfix/Session.h>
#include <quickfix/SessionSettings.h>
#include <quickfix/FileStore.h>
#include "quickfix/SocketInitiator.h"
#include "quickfix/ThreadedSocketAcceptor.h"
#include "quickfix/Log.h"
#include "Application.h"
#include <chrono>
#include <thread>
#include <vector>
#include <cstdio>
#include <httplib.h>
#include <string.h>
#include <iostream>
#include <string>
#include "json.hpp"
#include "DataBaseManager.h"



std::unordered_map<double, std::queue<FIX44::NewOrderSingle>> create_empty_orderbook() {
    return std::unordered_map<double, std::queue<FIX44::NewOrderSingle>>();
}

struct Stock{
    std::string stock_Ticker;
    std::unordered_map<double, std::queue<FIX44::NewOrderSingle>> buy_orderbook;
    std::unordered_map<double, std::queue<FIX44::NewOrderSingle>> sell_orderbook;

    //constructor
    Stock(std::string stockTicker): stock_Ticker(stockTicker){
          buy_orderbook = create_empty_orderbook();
          sell_orderbook = create_empty_orderbook();
    }
};

Stock ibmStock("IBM");
Stock nikeStock("NKE");
Stock teslaStock("TSLA");
Stock AmazonStock("AMZN");
Stock MetaStock("META");
Stock MicrosoftStock("MSFT");




