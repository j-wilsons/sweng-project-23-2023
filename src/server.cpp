// Server side C/C++ program to demonstrate Socket programming
// Server - inspired by GeeksforGeeks
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string>
#include <string.h>
#include <sstream>
#include <vector>


using namespace std;

#define PORT 5555
int server_fd, new_socket, valread;


using namespace std;



//checks the string inpput could be a number
bool isNum(string input){
    for(int i=0;i<input.size();i++){
        if(isdigit(input[i])==0){
            return false;
        }
    }
    return true;
}

//check if the input is in a correct form: orderType, Quantity, companyName
bool isCorrectForm(vector<string> input){
    if(input.size()>=3 && (input[0]=="Buy"||input[0]=="Sell")&&isNum(input[1])){
        return true;
    }
    return false;
}
//concatanates the rest of the inpupt, if the Company name is longer than 1 word
string concatVec(vector<string>input){
    string result="";
    for(int i=2;i<input.size()-1;i++){
        result=result+input[i]+" ";
    } 
    result=result+input[input.size()-1];
    return result;
}

int tradeExecution(string companyName, int orderQuantity) {
    int randomNumber;
    while(orderQuantity >= 5) {
        //randomNumber = rand()%(orderQuantity+ 1) + orderQuantity;
        randomNumber = 0 + (rand() % orderQuantity);
        orderQuantity -= randomNumber;
        printf("%d shares traded\n", randomNumber);
        sleep(1);
    }
    printf("All shares executed for %s \n", companyName.c_str());
    return 0;
}
string userInput(){
    string str;
    cout<<"----Type 'quit' to exit or press anything to continue----"<<endl;
    getline(cin, str);              // Taking in user's order
    return str;
}
void notifyClient(){
    send(new_socket, "----Trade Executed----", strlen("----Trade Executed----"), 0);
}

int main()
{
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    char buffer[1024] = {0};

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        cout << "socket failed" << endl;
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                   &opt, sizeof(opt)))
    {
        cout << "socket failed" << endl;
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address,
             sizeof(address)) < 0)
    {
        cout << "bind failed" << endl;
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0)
    {
        cout << "listen" << endl;
        exit(EXIT_FAILURE);
    }
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                             (socklen_t *)&addrlen)) < 0)
    {
        cout << "accept" << endl;
        exit(EXIT_FAILURE);
    }
    while(true){
        string cmdInput=userInput();
        if(cmdInput=="quit"){
            return 0;
        }
        cout<<"----waiting for client input----"<<endl;
        valread = read(new_socket, buffer, 1024);
        //cout << buffer << endl;
        if(strcmp(buffer, "quit")==0){
            cout<<"------client quit-------"<<endl;
        }else{
            //stringformatting starts here
            int orderQuantity;
            string  item, clientInput, companyName, orderType; //input: string from the client
            clientInput=string(buffer);                        //the "buffer" is from the client
            vector<string> items;
            stringstream ss(clientInput);
            while (std::getline(ss, item, ' ')) {
                items.push_back(item);
            }
            if(isCorrectForm(items)){
                orderType=items[0];
                orderQuantity=(int) stoi(items[1]);
                companyName=concatVec(items);

            }else{
                cout<<"----bad form----"<<endl;
            }
            tradeExecution(companyName, orderQuantity);
            notifyClient();
            cout << "----Trade Executed----" << endl;
        }
    }
    return 0;
}