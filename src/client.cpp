#include <quickfix/Message.h>
#include <quickfix/Session.h>
#include <quickfix/SessionSettings.h>
#include <quickfix/FileStore.h>
#include <quickfix/ThreadedSocketAcceptor.h>
#include "quickfix/FileLog.h"
#include "quickfix/SocketAcceptor.h"
#include "Application.h"
#include <string>
#include "quickfix/SocketInitiator.h"

int main()
{
    try
    {
        FIX::SessionSettings settings("../../src/client.cfg");
        Application application;
        FIX::FileStoreFactory storeFactory(settings);
        FIX::ScreenLogFactory logFactory(settings);
        FIX::SocketInitiator initiator(application, storeFactory, settings, logFactory);
        initiator.start();
        while (true) {
            char value;
            std::cin >> value;

            const std::string& Symbol = "TSLA";
            int Quantity = 100;
            try{
                application.run(application.sessionId_, Symbol, Quantity);
            }catch(std::exception & e){
                std::cout << e.what();
            }
        }
        return 0;
    }
    catch (FIX::ConfigError& e)
    {
        std::cout << e.what();
        while (true) {
            //FIX::process_sleep(1);
        }
        return 1;
    }
}

