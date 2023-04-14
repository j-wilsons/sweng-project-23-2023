#include <quickfix/Application.h>
#include <quickfix/Message.h>
#include <quickfix/Session.h>
#include <quickfix/SessionSettings.h>
#include <quickfix/FileStore.h>
#include "quickfix/SocketInitiator.h"
#include "quickfix/ThreadedSocketAcceptor.h"
#include "quickfix/Log.h"
#include "Application.h"
#include "MatchingEngine.h"
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
