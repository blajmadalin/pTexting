#include <iostream>
#include <sys/socket.h>     //socket :)
#include <netinet/in.h>     // for sockaddr_in, htons(), INADDR_ANY
#include <unistd.h>         // for close()
#include <cstring> 
#include <stdio.h>
#include <arpa/inet.h>


int main(){
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
    std::cout<<"Client connected \n";

    while(true){
        std::string message;
        getline(std::cin, message);
        send(clientSocket, message.c_str(), message.size(), 0);
    }
    
    return 0;

}