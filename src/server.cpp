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
#include <cstdio>
#include "curl/curl.h"
#include <iostream>
#include <string>

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}



int main(int argc, char* argv[]) {
    try
    {
        // delete from here

       std::string api_key = "EPD436H91DGONRID"; // replace with your own API key
    std::string url_base = "https://www.alphavantage.co/query?function=GLOBAL_QUOTE&symbol=";
    std::vector<std::string> symbols = {"AAPL", "GOOG", "TSLA", "AMZN"}; // replace with your desired symbols

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
    }//
        
        // to here

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
