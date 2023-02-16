#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <sstream>
using namespace std;

#define PORT 5555

bool isNum(string input)
{
    for (int i = 0; i < input.size(); i++)
    {
        if (isdigit(input[i]) == 0)
        {
            return false;
        }
    }
    return true;
}

bool isCorrectForm(string input)
{
    // tokenise
    string item;
    vector<string> items;
    stringstream ss(input);
    while (getline(ss, item, ' '))
    {
        items.push_back(item);
    }

    // checking corret formatting
    if ((items.size() >= 3 && (items[0] == "Buy" || items[0] == "Sell") && isNum(items[1])) || items[0] == "quit")
    {
        return true;
    }
    return false;
}

string userInput(){
    string str;
    cout<<"Enter order: or type 'quit' to exit"<<endl;
    getline(cin, str);              // Taking in user's order
    return str;
}

int main()
{
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    srand(time(NULL));

    char buffer[1024] = {0};
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        std::cout << "Socket creation error" << std::endl;
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "172.21.0.3", &serv_addr.sin_addr) <= 0) // LOCAL
    // if(inet_pton(AF_INET, "172.17.0.2", &serv_addr.sin_addr)<=0)  //CLIENT DOES NOT RUN IS CONTAINER
    // if(inet_pton(AF_INET, "172.21.0.1", &serv_addr.sin_addr)<=0) //CONTAINER
    // if(inet_pton(AF_INET, "10.0.9.1", &serv_addr.sin_addr)<=0) //OVERLAY
    {
        std::cout << "Address is invalid ... " << std::endl;
        return -1;
    }
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        std::cout << "Connection Failed. Try again! ..." << std::endl;
        return -1;
    }    
    // Getting Order
    string str;
    while(true)
    {   
        do //user input
        {
            str = userInput();
            if (isCorrectForm(str))
            {
                break;
            }
            cout << "----Order is not Correctly formatted----" << endl;
            cout << "Please follow: Buy/Sell Quantity CompanyName or type 'quit' to exit" << endl;
        } while (true);
        if (str == "quit")
        {
            char *cstr = &str[0];              //
            send(sock, cstr, strlen(cstr), 0);
            std::cout << "----Message sent---- " << std::endl;
            return 0;
        }


        char *cstr = &str[0];              //
        send(sock, cstr, strlen(cstr), 0);
        cout << "----Message sent ----" << std::endl;

        // check for new message from server
        // check if message is "Trade Executed", print it and exit
        valread = read(sock, buffer, 1024);        
        if (strcmp(buffer, "----Trade Executed----") == 0)
        {
            cout<<"----'"<<str<<"' executed----"<<endl;
        }else{
            cout<<"----Trade was not executed:----"<<endl;
        }
        // null terminate buffer to avoid garbage values from previous messages
        buffer[valread] = '\0';
        cout<<"----Waiting for Server----"<<endl;
    }
    return 0;
}
