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

#define PORT 5555

int main()
{
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    char buffer[1024] = {0};

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        std::cout << "socket failed" << std::endl;
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                   &opt, sizeof(opt)))
    {
        std::cout << "socket failed" << std::endl;
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address,
             sizeof(address)) < 0)
    {
        std::cout << "bind failed" << std::endl;
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0)
    {
        std::cout << "listen" << std::endl;
        exit(EXIT_FAILURE);
    }
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                             (socklen_t *)&addrlen)) < 0)
    {
        std::cout << "accept" << std::endl;
        exit(EXIT_FAILURE);
    }

    double pi = 3.1415;
    std::string str1 = "server => ";
    std::string str2 = std::to_string(pi);

    valread = read(new_socket, buffer, 1024);
    std::cout << buffer << std::endl;
    std::string str = str1 + " : " + str2 + " and " + buffer;
    char *cstr = &str[0];

    send(new_socket, cstr, strlen(cstr), 0);
    std::cout << "Message has been sent!" << std::endl;

    return 0;
}