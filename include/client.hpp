#include "quickfix/Message.h"
#include "quickfix/Session.h"
#include "quickfix/SessionSettings.h"
#include "quickfix/FileStore.h"
#include "quickfix/ThreadedSocketAcceptor.h"
#include "quickfix/FileLog.h"
#include "quickfix/SocketAcceptor.h"
#include "../src/Application.h"
#include "quickfix/SocketInitiator.h"
#include <string>
using namespace std;

std::string userInput();
bool isNum(string input);
bool isCorrectForm(string input);
int sums(int a, int b, int c);
