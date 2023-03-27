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
#include <httplib.h>
#include <string.h>

std::string getDataFromServer() {
    httplib::Client cli("localhost", 3000);
    std::cout << "Client started" << std::endl;
    auto res = cli.Get("/");
    if (res && res->status == 200) {
        return res->body;
    } else {
        std::cerr << "Error getting data: " << res.error() << std::endl;
        return "";
    }
}
int main(int argc, char* argv[]) {
    try
    {
        FIX::SessionSettings settings("../../src/server.cfg");
        Application application;
        FIX::FileStoreFactory storeFactory(settings);
        FIX::ScreenLogFactory logFactory(settings);
        FIX::ThreadedSocketAcceptor acceptor(application, storeFactory, settings, logFactory);
        acceptor.start();
        std::string asd=getDataFromServer();
        std::cout<<asd<<std::endl;
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