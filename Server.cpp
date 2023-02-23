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



int main(int argc, char* argv[]) {
    try
    {
        FIX::SessionSettings settings("../../server.cfg");
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