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
#include "curl/curl.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
   try
    {
        
        FIX::SessionSettings settings("../../src/server.cfg");
        Application application;
        std::vector<std::string> symbols = {"AAPL"};
        std::vector<std::string> responses = application.marketData(symbols);
        for (const auto& response : responses) {
            double MarketPrice = extract_key(response, "regularMarketPrice");
            std::cout << "Market price : " << MarketPrice << std::endl;
            std::cout << "Response: " << response << std::endl;
        }
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
